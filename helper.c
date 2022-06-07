#include <stdio.h>
#include <math.h>
#include <helper.h>
#include <stdlib.h>




char* machine_code_cell_to_string(MachineCodeCell *cell) {
    char *result = malloc(sizeof(char) * 10);
    sprintf(result, CELL_TO_BINARY_PATTERN, CELL_TO_BINARY(cell->opcode, cell->source_address, cell->dest_address, cell->encoding_type));
    return result;
}

void slice_str(const char * str, char * buffer, int start, int end)
{
    int j = 0;
    for ( int i = start; i <= end; ++i ) {
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

char *trim_whitespace(char *str) {
    char *end;
    // Trim leading space
    while(isspace(*str)) str++;
    if(*str == 0) {
        return str;
    }
    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    end[1] = '\0';

    return str;
}