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
    token = strtok(NULL, "");
    if (token == NULL) {
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

            strncpy(operand_2, token + i + 1, strlen(token) - i);
            if (strlen(operand_2) == 0) {
                operand_2 = NULL;
            }
            instruction->operand_2 = trim_whitespace(operand_2);
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
    if (strlen(token) == 0) {
        instruction->operand_1 = NULL;
    }
    else {
        instruction->operand_1 = trim_whitespace(token);
    }
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
    MachineCodeCell *cell = malloc(sizeof(MachineCodeCell));
    cell = parse_instruction(instruction);
    cell->encoding_type = ENCODING_TYPE_A;
    // printf("opcode: %d\n", cell->opcode);
    // return machine_code_cell_to_string(cell);
    return line;
}