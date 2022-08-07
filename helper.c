/* includes generic methods for the rest of the code to use */ 
#include <stdio.h>
#include <math.h>
#include "helper.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int has_found_error = 0;



CodeCell *header_code_cell_to_code_cell(HeaderCodeCell *header_code_cell)
{
    int data;
    CodeCell *code_cell = malloc(sizeof(CodeCell));
    code_cell->encoding_type = ENCODING_TYPE_A;
    data = header_code_cell->opcode;
    data = data << 2;
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

char *code_cell_to_b32(CodeCell *code_cell)
{
    char *base32 = malloc(sizeof(char) * 2);
    int data = code_cell->data;
    data = data << 2;
    data = data | code_cell->encoding_type;
    base32[0] = b32[(data >> 5)];
    base32[1] = b32[data ^ (data >> 5 << 5)];
    if (base32[0] == '!') {
        base32++;
    }
    return base32;
}


char* int_to_base_32(int data) {
    char *base32 = malloc(sizeof(char) * 2);
    base32[0] = b32[(data >> 5)];
    base32[1] = b32[data ^ (data >> 5 << 5)];
    if (base32[0] == '!') {
        base32++;
    }
    return base32;
}
void slice_str(const char *str, char *buffer, int start, int end)
{
    int i;
    int j = 0;
    for (i = start; i <= end; ++i)
    {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

char *trim_whitespace(char *str)
{
    char *end;
    /* Trim leading space */
    while (isspace(*str))
        str++;
    if (*str == 0)
    {
        return str;
    }

    /* Trim trailing space */
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
        end--;
    end[1] = '\0';

    return str;
}