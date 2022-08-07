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

DataInstruction* parse_data_instruction(char *line) {
    int i;
    char* operand_1;
    char* operand_2;
    DataInstruction *instruction = malloc(sizeof(DataInstruction));
    char *token = strtok(line, " \t");
    if (token == NULL) {
        strcpy(instruction->opcode, trim_whitespace(line));
        return instruction;
    }
    if (token[strlen(token) - 1] == ':') { /*CR - what if we have spaces between the label and the colon? */
        char* label = malloc(sizeof(char) * (strlen(token) - 1));
        strncpy(label, token, strlen(token) - 1);
        strcpy(instruction->label, trim_whitespace(label));
        validate_label(instruction->label);
        token = strtok(NULL, " \t");
    }

    strcpy(instruction->opcode, trim_whitespace(token));
    token = strtok(NULL, "");
    if (token == NULL) {
        return instruction;
    }
    operand_1 = malloc(sizeof(char) * strlen(token));
    operand_2 = malloc(sizeof(char) * strlen(token));
    for (i = 0; i < strlen(token); i++) {
        if (token[i] == ',') {
            strncpy(operand_1, token, i);
            if (strlen(operand_1) == 0) {
                operand_1 = NULL;
                printf("Found empty operand 1 with , \n");
                has_found_error = 1;
            }
            strcpy(instruction->operand_1, trim_whitespace(operand_1));

            strncpy(operand_2, token + i + 1, strlen(token) - i);
            if (strlen(operand_2) == 0) {
                printf("Invalid empty operand\n");
                has_found_error = 1;
            }

            strcpy(instruction->operand_2, trim_whitespace(operand_2));
            return instruction;
        }
    }
    /* no "," */
    if (strlen(trim_whitespace(token)) != 0) {
        strcpy(instruction->operand_1, trim_whitespace(token));
    }
    return instruction;
}

GuidingInstruction* parse_guiding_line_to_struct(char* line) {
    char *token;
    GuidingInstruction* guidance = malloc(sizeof(GuidingInstruction));
    strcpy(guidance->label, "1NULL");
    token = strtok(line, " \t");
    if (token[strlen(token) - 1] == ':') {
        char* label = malloc(sizeof(char) * (strlen(token) - 1));
        strncpy(label, token, strlen(token) - 1);
        strcpy(guidance->label, label);
        validate_label(guidance->label);
        token = strtok(NULL, " \t");
    }
    strcpy(guidance->guidance_word, trim_whitespace(token));
    validate_guidance_word(guidance->guidance_word);
    if ((strcmp(guidance->guidance_word, ".entry") || strcmp(guidance->guidance_word, ".extern"))
        && guidance->label != NULL)
        {
            strcpy(guidance->label, "1NULL");
            printf("Warning: .entry and .extern guidance words should not have labels. Ignoring label");
        }
    token = strtok(NULL, "\n");
    strcpy(guidance->guidance_input, token);
    return guidance;
}

int parse_instruction_line(char *line) {
    DataInstruction *instruction = parse_data_instruction(line);
    printf("Label: %s|\n", instruction->label);
    printf("Opcode: %s|\n", instruction->opcode);
    printf("Operand 1: %s|\n", instruction->operand_1);
    printf("Operand 2: %s|\n", instruction->operand_2);
    return parse_instruction(instruction);
}

int parse_guiding_line(char *line) {
    GuidingInstruction *guidance = parse_guiding_line_to_struct(line);
    printf("Label: %s|\n", guidance->label);
    printf("Guidance word: %s|\n", guidance->guidance_word);
    printf("Guidance input: %s|\n", guidance->guidance_input);
    return parse_guidance(guidance);
}