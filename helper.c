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
}

int is_ascii(char c) {
    if (c < 0 || c > 127) {
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


char *machine_code_cell_to_string(MachineCodeCell *cell)
{
    char *result = malloc(sizeof(char) * 10);
    sprintf(result, CELL_TO_BINARY_PATTERN, CELL_TO_BINARY(cell->opcode, cell->source_address, cell->dest_address, cell->encoding_type));
    return result;
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

// char* machine_code_to_b32(MachineCodeCell *cell) {

// char b32[] = {
//     '!',
//     '@',
//     '#',
//     '$',
//     '%',
//     '^',
//     '&',
//     '*',
//     '<',
//     '>',
//     'a',
//     'b',
//     'c',
//     'd',
//     'e',
//     'f',
//     'g',
//     'h',
//     'i',
//     'j',
//     'k',
//     'l',
//     'm',
//     'n',
//     'o',
//     'p',
//     'q',
//     'r',
//     's',
//     't',
//     'u',
//     'v',
// };

// }

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