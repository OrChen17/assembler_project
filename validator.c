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
    for (i = 1; i < strlen(token); i++)
    {
        if (!isdigit(token[i]) && ((token[i] == '+' && i != 1) || (token[i] == '-' && i != 1)))
        {
            printf("Invalid number: %s\n", token);
            has_found_error = 1;
            return;
        }
    }
    int number = atoi(token +  1);
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
    int i;
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

// TODO Or: validate address modes for opcodes operands (page 32)

void validate_opcode_operator_amount(int opcode, char *operator_1, char* operator_2)
{
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
