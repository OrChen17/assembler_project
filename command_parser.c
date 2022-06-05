#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <command_parser.h>

int long IC = 100;


void validate_number(char *token) {
    int i;
    for (i = 1; i < strlen(token); i++) {
        if (!isdigit(token[i]) || (i == 1 && (token[i] == '+' && token[i] == '-'))) {
            printf("Invalid number: %s\n", token);
            exit(1);
        }
    }
}


DataInstruction* parse_data_instruction(char *line) {
    DataInstruction *instruction = malloc(sizeof(DataInstruction));
    char *token = strtok(line, " ");
    if (token == NULL) {
        instruction->opcode = line;
        return instruction;
    }
    if (token[strlen(token) - 1] == ':') {
        char label[80];
        strncpy(label, token, strlen(token) - 1);
        instruction->label = label;
        token = strtok(NULL, " ");
    }

    //TODO: Tabs?
    instruction->opcode = token;
    if (token == NULL) {
        return instruction;
    }
    token = strtok(NULL, " ");
    if (token == NULL) {
        return instruction;
    }
    char* operand_1 = malloc(sizeof(char) * strlen(token));
    char* operand_2 = malloc(sizeof(char) * strlen(token));
    int is_string = 0;
    for (int i = 0; i < strlen(token); i++) {
        if (token[i] == ',' && is_string == 0) {
            strncpy(operand_1, token, i);
            instruction->operand_1 = operand_1;
            strncpy(operand_2, token + i, strlen(token) - i);
            instruction->operand_2 = operand_2;
            return instruction;
        }
        if (token == "\"" && is_string == 0) {
            is_string = 1;
        }
        if (token == "\"" && is_string == 1) {
            is_string = 0;
        }
    }
    // no ","
    instruction->operand_1 = token;
    instruction->operand_2 = NULL;
    return instruction;
}

char * parse_data_line(char *line) {
    IC++;
    DataInstruction *instruction = parse_data_instruction(line);
    printf("Label: %s|\n", instruction->label);
    printf("Opcode: %s|\n", instruction->opcode);
    printf("Operand 1: %s|\n", instruction->operand_1);
    printf("Operand 2: %s|\n", instruction->operand_2);
    // TODO: validate instruction
    // MachineCodeCell *cell = malloc(sizeof(MachineCodeCell));
    // cell->encoding_type = ENCODING_TYPE_A;
    // parse_opcode(cell, line);
    // parse_addr_modes(cell, line);
    // printf("opcode: %d\n", cell->opcode);
    // return machine_code_cell_to_string(cell);
    return line;
}