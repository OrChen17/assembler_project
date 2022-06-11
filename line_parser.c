#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <line_parser.h>
#include <instruction_parser.h>
#include <ctype.h>

DataInstruction* parse_data_instruction(char *line) {
    DataInstruction *instruction = malloc(sizeof(DataInstruction));
    instruction->label = NULL;
    instruction->operand_1 = NULL;
    instruction->operand_2 = NULL;
    char *token = strtok(line, " ");
    if (token == NULL) {
        instruction->opcode = trim_whitespace(line);
        return instruction;
    }
    if (token[strlen(token) - 1] == ':') {
        char* label = malloc(sizeof(char) * (strlen(token) - 1));
        strncpy(label, token, strlen(token) - 1);
        instruction->label = trim_whitespace(label);
        validate_label(instruction->label);
        token = strtok(NULL, " ");
    }

    instruction->opcode = trim_whitespace(token);
    token = strtok(NULL, "");
    if (token == NULL) {
        return instruction;
    }
    char* operand_1 = malloc(sizeof(char) * strlen(token));
    char* operand_2 = malloc(sizeof(char) * strlen(token));
    for (int i = 0; i < strlen(token); i++) {
        if (token[i] == ',') {
            strncpy(operand_1, token, i);
            if (strlen(operand_1) == 0) {
                operand_1 = NULL;
            }
            instruction->operand_1 = trim_whitespace(operand_1);

            strncpy(operand_2, token + i + 1, strlen(token) - i);
            if (strlen(operand_2) == 0) {
                printf("Invalid empty operand\n");
                has_found_error = 1;
            }

            instruction->operand_2 = trim_whitespace(operand_2);
            return instruction;
        }
    }
    // no ","
    if (strlen(trim_whitespace(token)) == 0) {
        instruction->operand_1 = NULL;
    }
    else {
        instruction->operand_1 = trim_whitespace(token);
    }
    instruction->operand_2 = NULL;
    return instruction;
}

int parse_data_line(char *line) {
    DataInstruction *instruction = parse_data_instruction(line);
    printf("Label: %s|\n", instruction->label);
    printf("Opcode: %s|\n", instruction->opcode);
    printf("Operand 1: %s|\n", instruction->operand_1);
    printf("Operand 2: %s|\n", instruction->operand_2);
    return parse_instruction(instruction);
}