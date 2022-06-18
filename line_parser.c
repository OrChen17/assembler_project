#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <line_parser.h>
#include <instruction_parser.h>
#include <ctype.h>
#include <validator.h>
#include <helper.h>

DataInstruction* parse_data_instruction(char *line) {
    DataInstruction *instruction = malloc(sizeof(DataInstruction)); // CR - it allocates 16 memory cells (for 4 addresses). If our instruction requires more than that, we might have a problem
    instruction->label = NULL;
    instruction->operand_1 = NULL;
    instruction->operand_2 = NULL;
    char *token = strtok(line, " \t");
    if (token == NULL) {
        instruction->opcode = trim_whitespace(line); //CR - strtok with space and tab already trims the spaces - both leading and trailing spaces 
        return instruction;
    }
    if (token[strlen(token) - 1] == ':') { //CR - what if we have spaces between the label and the colon?
        char* label = malloc(sizeof(char) * (strlen(token) - 1));
        strncpy(label, token, strlen(token) - 1);
        instruction->label = trim_whitespace(label); // CR - same comment as above
        validate_label(instruction->label);
        token = strtok(NULL, " \t");
    }
    // CR - we need here something like: if token == NULL --> missing opcode
    instruction->opcode = trim_whitespace(token); // CR - same comment
    token = strtok(NULL, " \t");
    if (token == NULL) {
        return instruction;
    }
    char* operand_1 = malloc(sizeof(char) * strlen(token));
    char* operand_2 = malloc(sizeof(char) * strlen(token));
    for (int i = 0; i < strlen(token); i++) {
        if (token[i] == ',') {
            strncpy(operand_1, token, i);
            if (strlen(operand_1) == 0) { // CR - doesn't it just mean that we had a comma with nothing before it --> an error ?
                operand_1 = NULL;
            }
            instruction->operand_1 = trim_whitespace(operand_1); // CR - here it's justified since the operand string was not achieved with strtok

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
    if (strlen(trim_whitespace(token)) == 0) { // CR - no need for the trim here
        instruction->operand_1 = NULL; // CR - the operands got NULL already in the beginning of the function, I think we can skip this
    }
    else {
        instruction->operand_1 = trim_whitespace(token); // CR - no need for the trim here
    }
    instruction->operand_2 = NULL; // CR - the operands got NULL already in the beginning of the function, I think we can skip this
    return instruction;
}

int parse_instruction_line(char *line) {
    DataInstruction *instruction = parse_data_instruction(line);
    printf("Label: %s|\n", instruction->label);
    printf("Opcode: %s|\n", instruction->opcode);
    printf("Operand 1: %s|\n", instruction->operand_1);
    printf("Operand 2: %s|\n", instruction->operand_2);
    return parse_instruction(instruction);
}