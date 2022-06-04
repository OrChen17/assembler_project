
#include <stdio.h>
#include <stdlib.h>
#include <file_handler.h>
#include <helper.h>

int is_empty_line(char *line) {
    for (int i = 0; i < strlen(line); i++) {
        if (!isspace(line[i])) {
            return 0;
        }
    }
    return 1;
}

int is_guiding_line(char *line) {
    char *token = strtok(line, " ");
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0) {
        return 1;
    }
    if (token == NULL) {
        return 0;
    }
    token = strtok(NULL, " ");
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
        return parse_guiding_line(line);
    }
    else {
        return parse_data_line(line);
    }

}

int assemble_file(FILE *input_file) { 
    char line[83];
    while (fgets(line, 83, input_file)) {
        parse_line(line);     
    }
    return 1;
}