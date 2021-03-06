#include <string.h>
#include <stdio.h>
#include <helper.h>
#include <stdlib.h>
#include <ctype.h>
#include <symbol_table.h>

int is_ascii(char c)
{
    if (c < 0x20 || c > 0x7e)
    {
        return 0;
    }
    return 1;
}

void validate_number(char *token)
{
    int i;
    int number;
    for (i = 1; i < strlen(token); i++)
    {
        if (!isdigit(token[i]) && ((token[i] == '+' && i != 1) || (token[i] == '-' && i != 1)))
        {
            printf("Invalid number: %s\n", token);
            has_found_error = 1;
            return;
        }
    }
    number = atoi(token +  1);
    if (number > 127 || number < -128)
    {
        printf("Invalid number out of range: %s\n", token);
        has_found_error = 1;
    }
}

void validate_ascii_string(char *token)
{
    int i;
    if (token[0] != '"')
    {
        printf("Invalid string: %s\n", token);
        has_found_error = 1;
    }
    for (i = 1; i < strlen(token) - 1; i++)
    {
        if (!is_ascii(token[i]))
        {
            printf("Invalid ascii string: %s\n", token);
            has_found_error = 1;
        }
    }
    if (token[strlen(token) - 1] != '"')
    {
        printf("Invalid string: %s\n", token);
        has_found_error = 1;
    }
}

void validate_label(char *label)
{
    int i;
    if (strlen(label) > 30)
    {
        printf("label too long: %s\n", label);
        has_found_error = 1;
    }
    if (!isalpha(label[0]))
    {
        printf("label must start with alphabet: %s\n", label);
        has_found_error = 1;
    }
    for (i = 1; i < strlen(label); i++)
    {
        if (!isalnum(label[i]))
        {
            printf("Invalid label: %s\n", label);
            has_found_error = 1;
        }
    }
    
    if (strcmp(label, "r0") == 0 || 
        strcmp(label, "r1") == 0 ||
        strcmp(label, "r2") == 0 ||
        strcmp(label, "r3") == 0 ||
        strcmp(label, "r4") == 0 ||
        strcmp(label, "r5") == 0 ||
        strcmp(label, "r6") == 0 ||
        strcmp(label, "r7") == 0 ||
        strcmp(label, "PSW") == 0)
        {
            printf("Invalid label - name is a register: %s\n", label);
            has_found_error = 1;
        }
     
    if (strcmp(label, "mov") == 0 || 
        strcmp(label, "cmp") == 0 ||
        strcmp(label, "add") == 0 ||
        strcmp(label, "sub") == 0 ||
        strcmp(label, "not") == 0 ||
        strcmp(label, "clr") == 0 ||
        strcmp(label, "lea") == 0 ||
        strcmp(label, "inc") == 0 ||
        strcmp(label, "dec") == 0 ||
        strcmp(label, "jmp") == 0 ||
        strcmp(label, "bne") == 0 ||
        strcmp(label, "get") == 0 ||
        strcmp(label, "prn") == 0 ||
        strcmp(label, "jsr") == 0 ||
        strcmp(label, "rts") == 0 ||
        strcmp(label, "hlt") == 0)
        {
            printf("Invalid label - name is an operand: %s\n", label);
            has_found_error = 1;
        }
    
    if (is_label_in_symbol_list(label))
    {
        printf("Duplicate label: %s\n", label);
        has_found_error = 1;
    }
}

void validate_guidance_word(char* guidance_word) {
    if (strcmp(guidance_word, ".data") != 0
        && strcmp(guidance_word, ".string") != 0
        && strcmp(guidance_word, ".struct") != 0
        && strcmp(guidance_word, ".entry") != 0
        && strcmp(guidance_word, ".extern") != 0)
    {
        printf("Invalid guidance word: %s\n", guidance_word);
        printf("Valid guidance words are: .data, .string, .struct, .entry, .extern");
        has_found_error = 1;
    }
}

void validate_guidance_input(char* guidance_word, char* guidance_input)
{
    char* token;
    int i;
    char* guidance_input_tokenized = guidance_input; /*to avoid corruption */
    if (strcmp(guidance_word, ".data"))
    {
        /* verifying no traking commas */
        for (i = 0; i < strlen(guidance_input) - 1; i++)
        {
            if (guidance_input[i] == ',' && guidance_input[i+1] == ',')
            {
                printf("Illegal input - tracking commas are not allowed");
                has_found_error = 1;
                break;
            }
        } 
        /* verifying all in list are ints */
        token = strtok(guidance_input_tokenized, ",");
        if (token == NULL) /* not sure it's necessary */
        {
            printf("empty input");
            has_found_error = 1;
        }
        while (token != NULL)
        {
            if (!atoi(trim_whitespace(token))) /*TODO - make sure it only trims on outer margins */
            {
                printf(".data input has to be a list of numbers, separated by commas");
                has_found_error = 1;
            }
            token = strtok(NULL, ",");
        }
    }

    else if (strcmp(guidance_word, ".string"))
    {
        validate_ascii_string(trim_whitespace(guidance_input));
    }

    else if (strcmp(guidance_word, ".struct"))
    {
        /* TODO - add tracking commas validation*/
        token = strtok(guidance_input_tokenized, ",");
        if (!atoi(trim_whitespace(token)))
        {
            printf(".struct input must start with a number");
            has_found_error = 1;
        }
        token = strtok(NULL, " \t");
        validate_ascii_string(token);

    }
    else
    {
        validate_label(trim_whitespace(guidance_input));
    }
}

const int valid_src_addr_modes[16][4] = {
    {0,1,2,3}, 
    {0,1,2,3}, 
    {0,1,2,3}, 
    {0,1,2,3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {-1, 1, 2, -1}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}
};

const int valid_dest_addr_modes[16][4] = {
    {-1, 1,2,3}, 
    {0,1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {-1, 1,2,3}, 
    {0,1,2,3}, 
    {-1, 1,2,3}, 
    {0, 1, 2, 3}, 
    {0, 1, 2, 3}
};

void validate_src_address_mode_for_opcode(int opcode, int address_mode) {
    if (-1 == valid_src_addr_modes[opcode][address_mode]) {
        printf("Invalid src address mode for opcode: %d\n", opcode);
        has_found_error = 1;
    }
}

void validate_dest_address_mode_for_opcode(int opcode, int address_mode) {
    if (-1 == valid_dest_addr_modes[opcode][address_mode]) {
        printf("Invalid dest address mode for opcode: %d\n", opcode);
        has_found_error = 1;
    }
}

void validate_opcode_operator_amount(int opcode, char *operator_1, char* operator_2)
{
    const int OPCODE_OPERATOR_AMOUNTS[] = {2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0};

    int amount = 0;
    if (operator_1 != NULL)
    {
        amount++;
    }
    if (operator_2 != NULL)
    {
        amount++;
    }
    if (amount != OPCODE_OPERATOR_AMOUNTS[opcode])
    {
        printf("Invalid amount of operands for opcode: %d, Expected: %d, Got: %d\n", opcode, OPCODE_OPERATOR_AMOUNTS[opcode], amount);
        has_found_error = 1;
    }
}
