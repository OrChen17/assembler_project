#include <stdio.h>
#include <stdlib.h>
#include <helper.h>
#include <string.h>
#include "file_handler.h"
#include <line_parser.h>
#include <ctype.h>

int is_empty_line(char *line) {
    for (int i = 0; i < strlen(line); i++) {
        if (!isspace(line[i])) {
            return 0;
        }
    }
    return 1;
}

int is_guiding_line(char *line_pointer) {
    // copy to protect original line
    char *line = malloc(sizeof(char) * strlen(line_pointer));
    strcpy(line, line_pointer);

    char *token = strtok(line, " ");
    if (token == NULL) {
        return 0;
    }
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0) {
        return 1;
    }
    token = strtok(NULL, " ");
    if (token == NULL) {
        return 0;
    }
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0) {
        return 1;
    }
    return 0;
}

int parse_line(char *line) {
    if (is_empty_line(line)) {
        return 0;
    }
    if (line[0] == ';') {
        // comment line
        return 0;
    }
    if (is_guiding_line(line)) {
        // return parse_guiding_line(line);
        return 0;
    }
    else {
        return parse_data_line(line);
    }

}

int assemble_file(FILE *input_file) { 
    char line[83];
    while (fgets(line, 83, input_file)) {
        printf("Got line: %s\n", line);
        parse_line(line);     
    }
    return 1;
}