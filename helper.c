#include <stdio.h>
#include <math.h>
#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void validate_number(char *token) {
    int i;
    for (i = 1; i < strlen(token); i++) {
        if (!isdigit(token[i]) || (i == 1 && (token[i] == '+' && token[i] == '-'))) {
            printf("Invalid number: %s\n", token);
            exit(1);
        }
    }
    // #check number out of range
}

int is_ascii(char c) {
    if (c < 0x20 || c > 0x7e) {
        return 0;
    }
    return 1;
}

void validate_ascii_string(char *token) {
    int i;
    if (token[0] != '"') {
        printf("Invalid string: %s\n", token);
        exit(1);
    }
    for (i = 1; i < strlen(token) - 1; i++) {
        if (!is_ascii(token[i])) {
            printf("Invalid ascii string: %s\n", token);
            exit(1);
        }
    }
    if (token[strlen(token) - 1] != '"') {
        printf("Invalid string: %s\n", token);
        exit(1);
    }
}
// todo: add validators per operand - add shouldnt have strings etc. move to validator.c file
void validate_label(char *label) {
    if (strlen(label) > 30) {
        printf("label too long: %s\n", label);
        exit(1);
    }
    if (!isalpha(label[0])) {
        printf("label must start with alphabet: %s\n", label);
        exit(1);
    }
    int i;
    for (i = 1; i < strlen(label); i++) {
        if (!isalnum(label[i])) {
            printf("Invalid label: %s\n", label);
            exit(1);
        }
    }
    // TODO: check if label already exists
    // TODO: check if operand name / register name
}

CodeCell* header_code_cell_to_code_cell(HeaderCodeCell *header_code_cell) {
    CodeCell *code_cell = malloc(sizeof(CodeCell));
    code_cell->encoding_type = ENCODING_TYPE_A;
    int data = header_code_cell->opcode;
    data = data << 4;
    data = data | header_code_cell->source_address;
    data = data << 2;
    data = data | header_code_cell->dest_address;
    code_cell->data = data;
    return code_cell;
}

char b32[] = {
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '<',
    '>',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
};

char* code_cell_to_b32(CodeCell *code_cell) {
    char* base32 = malloc(sizeof(char) * 2);
    int data = code_cell->data;
    data = data << 2;
    data = data | code_cell->encoding_type;
    base32[0] = b32[(data >> 5)];
    base32[1] = b32[data ^ (data >> 5 << 5)];
    return base32;
}


void slice_str(const char *str, char *buffer, int start, int end)
{
    int j = 0;
    for (int i = start; i <= end; ++i)
    {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}


char *trim_whitespace(char *str)
{
    char *end;
    // Trim leading space
    while (isspace(*str))
        str++;
    if (*str == 0)
    {
        return str;
    }
    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
        end--;
    end[1] = '\0';

    return str;
}