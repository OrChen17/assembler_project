/*This file process each file line by line, checks which type of line it is, 
and calls line_parser according to the type of file it is*/
#include <stdio.h>
#include <stdlib.h>
#include <helper.h>
#include <string.h>
#include "file_handler.h"
#include <line_parser.h>
#include <ctype.h>

int is_empty_line(char line[83]) {
    int i;
    for (i = 0; i < strlen(line); i++) {
        if (!isspace(line[i])) {
            return 0;
        }
    }
    return 1;
}

int is_guiding_line(char line[83]) {
    /*checks if the line is a guiding-type line*/
    char *token;
    char line_to_parse[83];
    /* copy to protect original line */
    strcpy(line_to_parse, line);

    token = strtok(line_to_parse, " \t\n");
    if (token == NULL) {
        return 0;
    }
    /* checking if the 1st word in the line is a guiding word */
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0
        || strcmp(token, ".entry") == 0) {
        return 1;
    }
    token = strtok(NULL, " \t\n");
    if (token == NULL) {
        return 0;
    }
    /* checking if the 2nd word in the line is a guiding word (the 1st one could be a label) */
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0
        || strcmp(token, ".entry") == 0) {
        return 1;
    }
    return 0;
}

int parse_line(char *line) {
    /*checks which type of line it is. returns 0 if everything is ok, otherwise 1
        parses the line if needed*/

    if (is_empty_line(line)) {
        return 0;
    }
    if (line[0] == ';') {
        return 0;
    }
    if (is_guiding_line(line)) {
        return parse_guiding_line(line);
    }
    else {
        return parse_instruction_line(line);
    }
}

int assemble_file(FILE *pre_assembled_file) { 
    /*runs the assembler on the file*/
    char line[83];
    while (fgets(line, 83, pre_assembled_file)) {
        if (strlen(line) > 81) {
            printf("Line \"%s\" is too long\n", line);
            has_found_error = 1;
        }
        else {
            printf("$$ Got line: %s", line);
            if (line[(strlen(line) - 1)] != '\n')
            {
                printf("\n");
            }
            parse_line(line);     
        }
    }
    return 1;
}