/* parses each line from its bare text to a "DataInstruction" / GuidingInstruction struct, 
which has the parsed sections of the line - label, operands, opcode etc. passes the instruction to the instruction parser */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <line_parser.h>
#include <instruction_parser.h>
#include <ctype.h>
#include <validator.h>
#include <helper.h>
#include <guidance_parser.h>

DataInstruction* parse_data_instruction(char *instruction_to_parse) {
    int i;
    char* operand_1;
    char* operand_2;
    DataInstruction *instruction = malloc(sizeof(DataInstruction));
    char *token;
    strcpy(instruction->label, "");
    token = strtok(instruction_to_parse, " \t\n");
    if (token == NULL) {
        strcpy(instruction->opcode, trim_whitespace(instruction_to_parse));
        return instruction;
    }
    if (token[strlen(token) - 1] == ':') { /* ##CR: what if we have spaces between the label and the colon? */
        char* label = malloc(sizeof(char) * (strlen(token) - 1));
        strncpy(label, token, strlen(token) - 1);
        label[strlen(token) - 1] = '\0';
        strcpy(instruction->label, trim_whitespace(label));
        validate_label(instruction->label);
        check_duplicate_label(instruction->label);
        token = strtok(NULL, " \t\n");
    }

    strcpy(instruction->opcode, trim_whitespace(token));
    token = strtok(NULL, "");
    if (token == NULL) {
        return instruction;
    }
    operand_1 = malloc(sizeof(char) * strlen(token) + 1);
    operand_2 = malloc(sizeof(char) * strlen(token) + 1);
    for (i = 0; i < strlen(token); i++) {
        if (token[i] == ',') {
            strncpy(operand_1, token, i);
            operand_1[i] = '\0';
            if (strlen(operand_1) == 0) {
                operand_1 = NULL;
                printf("Found empty operand 1 with , \n");
                /* ##CR: When getting here (with proper example) --> segfault */
                has_found_error = 1;
            }
            strcpy(instruction->operand_1, trim_whitespace(operand_1));

            strncpy(operand_2, token + i + 1, strlen(token) - i); /* ##CR: add null terminator */
            if (strlen(operand_2) == 0) {
                printf("Invalid empty operand\n");
                has_found_error = 1;
            }

            strcpy(instruction->operand_2, trim_whitespace(operand_2));
            return instruction;
        }
    }
    /* ##CR: no "," */
    if (strlen(trim_whitespace(token)) != 0) {
        strcpy(instruction->operand_2, trim_whitespace(token));
    }
    return instruction;
}

GuidingInstruction* parse_guiding_line_to_struct(char* guidance_to_parse) {
    char *token;
    GuidingInstruction* guidance = malloc(sizeof(GuidingInstruction));
    strcpy(guidance->label, "");
    token = strtok(guidance_to_parse, " \t\n");
    if (token[strlen(token) - 1] == ':') {
        char* label = malloc(sizeof(char) * (strlen(token) + 10)); /* ##CR: try to look for a better solution */
        strncpy(label, token, strlen(token) - 1);
        label[strlen(token) - 1] = '\0';
        strcpy(guidance->label, trim_whitespace(label));
        validate_label(guidance->label);
        check_duplicate_label(guidance->label);
        token = strtok(NULL, " \t\n");
    }
    strcpy(guidance->guidance_word, trim_whitespace(token));
    validate_guidance_word(guidance->guidance_word);
    if (!(strcmp(guidance->guidance_word, ".entry") || !strcmp(guidance->guidance_word, ".extern"))
        && strcmp(guidance->label, ""))
        {
            strcpy(guidance->label, "");
            printf("Warning: .entry and .extern guidance words should not have labels. Ignoring label\n");
        }
    token = strtok(NULL, "\n");
    strcpy(guidance->guidance_input, token);
    return guidance;
}

int parse_instruction_line(char *instruction_to_parse) {
    DataInstruction *instruction = parse_data_instruction(instruction_to_parse);
    printf("Label: %s|\n", instruction->label);
    printf("Opcode: %s|\n", instruction->opcode);
    printf("Operand 1: %s|\n", instruction->operand_1);
    printf("Operand 2: %s|\n", instruction->operand_2);
    return parse_instruction(instruction);
}

int parse_guiding_line(char *guidance_to_parse) {
    GuidingInstruction *guidance = parse_guiding_line_to_struct(guidance_to_parse);
    printf("Label: %s|\n", guidance->label);
    printf("Guidance word: %s|\n", guidance->guidance_word);
    printf("Guidance input: %s|\n", guidance->guidance_input);
    return parse_guidance(guidance);
}