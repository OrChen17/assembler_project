#ifndef COMMAND_PARSER
#define COMMAND_PARSER

typedef struct data_instruction {
    char* label;
    char* opcode;
    char* operand_1;
    char* operand_2;
} DataInstruction;

char * parse_data_line(char *line);
#endif