/*This file process each file line by line, checks which type of line it is, 
and calls line_parser according to the type of file it is*/
#include <stdio.h>
#include <stdlib.h>
#include <helper.h>
#include <string.h>
#include "file_handler.h"
#include <line_parser.h>
#include <ctype.h>

int is_empty_line(char *line) {
    int i;
    for (i = 0; i < strlen(line); i++) {
        if (!isspace(line[i])) {
            return 0;
        }
    }
    return 1;
}

int is_guiding_line(char *line_pointer) {
    /*checks if the line is a guiding-type line*/
    char *token;
    /* copy to protect original line */
    char *line = malloc(sizeof(char) * strlen(line_pointer));
    strcpy(line, line_pointer);

    token = strtok(line, ""); /* empty string or space? Assuming space, I think we need also tabs */
    /* CR - I still think we don't need this, since ff there are no spaces then the line only has a \n, but isspace() also recognizes the \n char */
    if (token == NULL) {
        return 0;
    }
    if (strcmp(token, ".data") == 0
        || strcmp(token, ".string") == 0
        || strcmp(token, ".struct") == 0
        || strcmp(token, ".extern") == 0
        || strcmp(token, ".entry") == 0) {
        return 1;
    }
    /*I still don't get why we need this duplication*/
    token = strtok(NULL, " ");
    if (token == NULL) {
        return 0;
    }
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
            printf("Got line: %s\n", line);
            parse_line(line);     
        }
    }
    return 1;
}