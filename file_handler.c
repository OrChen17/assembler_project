#include <stdio.h>
#include <stdlib.h>
#include <helper.h>
#include <string.h>
#include <file_handler.h>
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
        return 0; /* ##CR: Wasn't this case covered when we check if the line is empty?
        I mean, token will be NULL at this point only if the line is empty. But if it's empty,
        we'll not get to this part of the code anyway */
    }
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0
        || strcmp(token, ".entry") == 0) {
        return 1; /* ##CR: It could also be a label. Need to add something like - if token is label --> check next word (labels have syntax rules that can be verified)
        Also, we need a 1st round that only looks for symbols and stores them in a symbols table (it's emphasized in the instructions) */
    }
    token = strtok(NULL, " ");
    if (token == NULL) {
        return 0; /* ##CR: printf("missing arguments") 
                     Also not that they emphasize that the program should keep running even when errors are encountered */
    }
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0
        || strcmp(token, ".entry") == 0) {
        return 1; /* ##CR: duplicate */
    }
    return 0;
}

char* parse_line(char *line) {
    if (is_empty_line(line)) {
        return NULL;
    }
    if (line[0] == ';') {
        // comment line
        return NULL;
    }
    if (is_guiding_line(line)) {
        // parse_data_line(line);
    }
    else {
        return parse_data_line(line);
    }

}

int assemble_file(FILE *input_file) { 
    char line[83];
    while (!feof(input_file)) {
        fgets(line, 83, input_file);
        printf("Got line: %s\n", line);
        if (parse_line(line) == NULL) {
           continue;
        }
        else {
            /* Do something */
        }
    }
    return 1;
}