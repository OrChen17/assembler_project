#include <helper.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int parse_opcode(HeaderCodeCell *cell, DataInstruction *instruction) {
    if (strcmp(instruction->opcode, "add") == 0) {
        return OPCODE_ADD;
    }
    if (strcmp(instruction->opcode, "cmp") == 0) {
        return OPCODE_CMP;
    }
    if (strcmp(instruction->opcode, "sub") == 0) {
        return OPCODE_SUB;
    }
    if (strcmp(instruction->opcode, "mov") == 0) {
        return OPCODE_MOV;
    }
    if (strcmp(instruction->opcode, "not") == 0) {
        return OPCODE_NOT;
    }
    if (strcmp(instruction->opcode, "clr") == 0) {
        return OPCODE_CLR;
    }
    if (strcmp(instruction->opcode, "lea") == 0) {
        return OPCODE_LEA;
    }
    if (strcmp(instruction->opcode, "inc") == 0) {
        return OPCODE_INC;
    }
    if (strcmp(instruction->opcode, "dec") == 0) {
        return OPCODE_DEC;
    }
    if (strcmp(instruction->opcode, "jmp") == 0) {
        return OPCODE_JMP;
    }
    if (strcmp(instruction->opcode, "bne") == 0) {
        return OPCODE_BNE;
    }
    if (strcmp(instruction->opcode, "get") == 0) {
        return OPCODE_GET;
    }
    if (strcmp(instruction->opcode, "prn") == 0) {
        return OPCODE_PRN;
    }
    if (strcmp(instruction->opcode, "jsr") == 0) {
        return OPCODE_JSR;
    }
    if (strcmp(instruction->opcode, "rts") == 0) {
        return OPCODE_RTS;
    }
    if (strcmp(instruction->opcode, "hlt") == 0) {
        return OPCODE_HLT;
    }
    else {
        printf("Invalid opcode: %s\n", instruction->opcode);
        exit(1);
    }
}

short int parse_addr_mode(HeaderCodeCell *cell, DataInstruction *instruction, char* operand) {
    if (operand == NULL) {
        return ADDR_MODE_IMMEDIATE;
    }
    if (operand[0] == '#') {
        validate_number(operand);
        return ADDR_MODE_IMMEDIATE;
    }
    if (operand[0] == '"') {
        printf("Invalid operand: strings should be as part of a label %s\n", operand);
        exit(1);
    }
    if (strcmp(operand, "r0") == 0 || 
        strcmp(operand, "r1") == 0 || 
        strcmp(operand, "r2") == 0 || 
        strcmp(operand, "r3") == 0 || 
        strcmp(operand, "r4") == 0 || 
        strcmp(operand, "r5") == 0 || 
        strcmp(operand, "r6") == 0 || 
        strcmp(operand, "r7") == 0) {
        return ADDR_MODE_REGISTER;
    }
    if (strstr(operand, ".") != NULL) {
        return ADDR_MODE_DIRECT_PARAM;
    }
    return ADDR_MODE_DIRECT;
}

void parse_instruction(DataInstruction *instruction) {
    HeaderCodeCell *cell = malloc(sizeof(HeaderCodeCell));

    cell->encoding_type = ENCODING_TYPE_A;
    cell->opcode = parse_opcode(cell, instruction);
    // TODO: validate correct number of operands and operand types

    cell->source_address = parse_addr_mode(cell, instruction, instruction->operand_1);
    cell->dest_address = parse_addr_mode(cell, instruction, instruction->operand_2);
    printf("Cell: opcode=%d source_address=%d dest_address=%d\n", cell->opcode, cell->source_address, cell->dest_address);
    // TODO: Add address cells
    // TODO: add machine code and data list
    // TODO: Add label to symbol chart

}