#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <line_parser.h>
#include <instruction_parser.h>

int long IC = 100;


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
        token = strtok(NULL, " ");
    }

    instruction->opcode = trim_whitespace(token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        /* Before returning the instruction - make sure this instruction should indeed have no arguments
        I guess we'll need a table of which instrutions should have how many arguments */
        return instruction;
    }
    char* operand_1 = malloc(sizeof(char) * strlen(token));
    char* operand_2 = malloc(sizeof(char) * strlen(token));
    int is_string = 0;
    for (int i = 0; i < strlen(token); i++) {
        if (token[i] == ',' && is_string == 0) {
            strncpy(operand_1, token, i);
            if (strlen(operand_1) == 0) {
                operand_1 = NULL;
            }
            instruction->operand_1 = trim_whitespace(operand_1);
            /* Maybe I'm missing something here, but it seems wrong. When there's only one operand it should be considered as operand_2 (the destination operand) */
            strncpy(operand_2, token + i + 1, strlen(token) - i);
            if (strlen(operand_2) == 0) {
                printf("Invalid empty operand\n");
                exit(1);
            }

            instruction->operand_2 = trim_whitespace(operand_2);
            /* Also here - before returning the instruction - make sure this instruction should indeed have the number of arguments it got */
            return instruction;
        }
        if (token[i] == '"' && is_string == 0) {
            is_string = 1;
        }
        else{
            if (token[i] == '"' && is_string == 1) {
               is_string = 0;
            }
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

char * parse_instruction_line(char *line) {
    IC++; /* Why? if the 1st line of the assembly file is an instruction line, then we want to assemble it into cell 100 */
    DataInstruction *instruction = parse_data_instruction(line);
    printf("Label: %s|\n", instruction->label);
    printf("Opcode: %s|\n", instruction->opcode);
    printf("Operand 1: %s|\n", instruction->operand_1);
    printf("Operand 2: %s|\n", instruction->operand_2);
    parse_instruction(instruction); /* Maybe convert_instruction (to machine language) would be a better name? */
    // printf("opcode: %d\n", cell->opcode);
    // return machine_code_cell_to_string(cell);
    return line;
}