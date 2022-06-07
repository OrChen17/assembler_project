#include <helper.h>
#include <string.h>

int parse_opcode(MachineCodeCell *cell, DataInstruction *instruction) {
    if (strcmp(instruction->opcode, "add") == 0) {
        cell->opcode = OPCODE_ADD;
        return 1;
    }
    if (strcmp(instruction->opcode, "cmp") == 0) {
        cell->opcode = OPCODE_CMP;
        return 1;
    }
    if (strcmp(instruction->opcode, "sub") == 0) {
        cell->opcode = OPCODE_SUB;
        return 1;
    }
    if (strcmp(instruction->opcode, "mov") == 0) {
        cell->opcode = OPCODE_MOV;
        return 1;
    }
    if (strcmp(instruction->opcode, "not") == 0) {
        cell->opcode = OPCODE_NOT;
        return 1;
    }
    if (strcmp(instruction->opcode, "clr") == 0) {
        cell->opcode = OPCODE_CLR;
        return 1;
    }
    if (strcmp(instruction->opcode, "lea") == 0) {
        cell->opcode = OPCODE_LEA;
        return 1;
    }
    if (strcmp(instruction->opcode, "inc") == 0) {
        cell->opcode = OPCODE_INC;
        return 1;
    }
    if (strcmp(instruction->opcode, "dec") == 0) {
        cell->opcode = OPCODE_DEC;
        return 1;
    }
    if (strcmp(instruction->opcode, "jmp") == 0) {
        cell->opcode = OPCODE_JMP;
        return 1;
    }
    if (strcmp(instruction->opcode, "bne") == 0) {
        cell->opcode = OPCODE_BNE;
        return 1;
    }
    if (strcmp(instruction->opcode, "get") == 0) {
        cell->opcode = OPCODE_GET;
        return 1;
    }
    if (strcmp(instruction->opcode, "prn") == 0) {
        cell->opcode = OPCODE_PRN;
        return 1;
    }
    if (strcmp(instruction->opcode, "jsr") == 0) {
        cell->opcode = OPCODE_JSR;
        return 1;
    }
    if (strcmp(instruction->opcode, "rts") == 0) {
        cell->opcode = OPCODE_RTS;
        return 1;
    }
    if (strcmp(instruction->opcode, "hlt") == 0) {
        cell->opcode = OPCODE_HLT;
        return 1;
    }
    else {
        printf("Invalid opcode: %s\n", instruction->opcode);
        exit(1);
    }
}

void parse_addr_modes(MachineCodeCell *cell, DataInstruction *instruction, char* operand, unsigned address:2) {
    // todo: check for more whitespace
    if (instruction->operand_1 == NULL) {
        cell->source_address = ADDR_MODE_IMMEDIATE;
        return;
    }
     if (instruction->operand_2 == NULL) {
        cell->dest_address = ADDR_MODE_IMMEDIATE;
        return;
    }

    if (instruction->operand_1[0] == '#') {
        validate_number(instruction->operand_1);
        cell->source_address = ADDR_MODE_IMMEDIATE;
    }
    if (instruction->operand_2[0] == '#') {
        validate_number(instruction->operand_2);
        cell->source_address = ADDR_MODE_IMMEDIATE;
    }

    if (strcmp(instruction->operand_1, "r0") == 0 || 
        strcmp(instruction->operand_1, "r1") == 0 || 
        strcmp(instruction->operand_1, "r2") == 0 || 
        strcmp(instruction->operand_1, "r3") == 0 || 
        strcmp(instruction->operand_1, "r4") == 0 || 
        strcmp(instruction->operand_1, "r5") == 0 || 
        strcmp(instruction->operand_1, "r6") == 0 || 
        strcmp(instruction->operand_1, "r7") == 0) {
        cell->source_address = ADDR_MODE_REGISTER;
    }
    if (strcmp(instruction->operand_2, "r0") == 0 || 
        strcmp(instruction->operand_2, "r1") == 0 || 
        strcmp(instruction->operand_2, "r2") == 0 || 
        strcmp(instruction->operand_2, "r3") == 0 || 
        strcmp(instruction->operand_2, "r4") == 0 || 
        strcmp(instruction->operand_2, "r5") == 0 || 
        strcmp(instruction->operand_2, "r6") == 0 || 
        strcmp(instruction->operand_2, "r7") == 0) {
        cell->dest_address = ADDR_MODE_REGISTER;
    }
    

}

void parse_instruction(DataInstruction *instruction, MachineCodeCell *cell) {
    parse_opcode(cell, line);
    parse_addr_modes(cell, line);
}