/*includes validation logic for the rest of the program */
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
        if (!isdigit(token[i]))
        {
            if (i == 1 && (token[i] == '+' || token[i] == '-')) {
                continue;
            }
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
    
    /* ##CR: add validation that label is not a guidance word */
}

void check_duplicate_label(char *label) {
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
        printf("Valid guidance words are: .data, .string, .struct, .entry, .extern\n");
        has_found_error = 1;
    }
}

void validate_no_tracking_commas(char guidance_input[200])
{
    int i;
    char *token;
    char guidance_input_tokenized[200];
    strcpy(guidance_input_tokenized, guidance_input); /*to avoid corruption */
    token = strtok(guidance_input_tokenized, " \t\n");
    while (token != NULL)
    {
        if (token[0] == ',')
        {
            printf("Invalid input: %s\n", guidance_input);
            has_found_error = 1;
            return;
        }
        for (i = 0; i < strlen(token) - 1; i++)
        {
            if (token[i] == ',' && token[i+1] == ',')
            {
                printf("Illegal input - tracking commas are not allowed\n");
                has_found_error = 1;
            }
        }
        token = strtok(NULL, " \t\n");
    }
}

void validate_number_for_guidance(char* token)
{
    int i;
    if (strlen(token) == 0) {
        printf("ERROR: .data input has to be a list of numbers, separated by commas");
        has_found_error = 1;
        return;
    }
    for (i = 1; i < strlen(token); i++)
    {
        if (!isdigit(token[i]) && ((token[i] == '+' && i != 1) || (token[i] == '-' && i != 1)))
        {
            printf("ERROR: .data input has to be a list of numbers, separated by commas");
            has_found_error = 1;
            return;
        }
    }
}

void validate_guidance_string_input(char* token)
{
    validate_ascii_string(trim_whitespace(token));
    if (token[0] != '\"' || token[strlen(token) - 1] != '\"' || strlen(token) < 2)
    {
        printf("ERROR: string inputs must start and and with a double quote\n");
        has_found_error = 1;
    }
    else if (strlen(token) == 2)
    {
        printf("ERROR: string input can't be and empty string\n");
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
    if (strcmp(operator_1, "") != 0)
    {
        amount++;
    }
    if (strcmp(operator_2, "") != 0)
    {
        amount++;
    }
    if (amount != OPCODE_OPERATOR_AMOUNTS[opcode])
    {
        printf("Invalid amount of operands for opcode: %d, Expected: %d, Got: %d\n", opcode, OPCODE_OPERATOR_AMOUNTS[opcode], amount);
        has_found_error = 1;
    }
}
/* ##CR: validation for "reshuma" is missing - "reshuma" can only have 2 fields after the "." sign - 1 or 2. Currently we accept others */
/* ##CR: when the opcode is invalid we print an opcode error, but also a dest and address error. Doesn't make sense. */
/* ##CR: consider a better error message when guidance is e.g. .string, - comma should be removed error instead of invalid opcode */
/* ##CR: in guidance (maybe also in instruction) - a comma at the end of the row should fail also with no spaces. Currently it passes */
/* ##CR: extern inputs missing validation - check that the label does NOT appear in the symbols table */