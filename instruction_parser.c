#include <helper.h>
#include <string.h>

int parse_opcode(MachineCodeCell *cell, char *line) {
    char *token = strtok(line, " ");
    if (strcmp(token, "add") == 0) {
        cell->opcode = OPCODE_ADD;
        return 1;
    }
    if (strcmp(token, "cmp") == 0) {
        cell->opcode = OPCODE_CMP;
        return 1;
    }
    if (strcmp(token, "sub") == 0) {
        cell->opcode = OPCODE_SUB;
        return 1;
    }
    if (strcmp(token, "mov") == 0) {
        cell->opcode = OPCODE_MOV;
        return 1;
    }
    if (strcmp(token, "not") == 0) {
        cell->opcode = OPCODE_NOT;
        return 1;
    }
    if (strcmp(token, "clr") == 0) {
        cell->opcode = OPCODE_CLR;
        return 1;
    }
    if (strcmp(token, "lea") == 0) {
        cell->opcode = OPCODE_LEA;
        return 1;
    }
    if (strcmp(token, "inc") == 0) {
        cell->opcode = OPCODE_INC;
        return 1;
    }
    if (strcmp(token, "dec") == 0) {
        cell->opcode = OPCODE_DEC;
        return 1;
    }
    if (strcmp(token, "jmp") == 0) {
        cell->opcode = OPCODE_JMP;
        return 1;
    }
    if (strcmp(token, "bne") == 0) {
        cell->opcode = OPCODE_BNE;
        return 1;
    }
    if (strcmp(token, "get") == 0) {
        cell->opcode = OPCODE_GET;
        return 1;
    }
    if (strcmp(token, "prn") == 0) {
        cell->opcode = OPCODE_PRN;
        return 1;
    }
    if (strcmp(token, "jsr") == 0) {
        cell->opcode = OPCODE_JSR;
        return 1;
    }
    if (strcmp(token, "rts") == 0) {
        cell->opcode = OPCODE_RTS;
        return 1;
    }
    if (strcmp(token, "hlt") == 0) {
        cell->opcode = OPCODE_HLT;
        return 1;
    }
    else {
        printf("Invalid opcode: %s\n", token);
        exit(1);
    }
}

void parse_addr_modes(MachineCodeCell *cell, char *line) {

    char *token = strtok(line, " ");
    // todo: check for more whitespace
    if (strcmp(token, "hlt") == 0 || strcmp(token, "rts") == 0) {
        cell->source_address = ADDR_MODE_IMMEDIATE;
        cell->dest_address = ADDR_MODE_IMMEDIATE;
        return;
    }

    token = strtok(NULL, ",");

    if (strcmp(token, "r0") == 0 || 
    strcmp(token, "r1") == 0 || 
    strcmp(token, "r2") == 0 || 
    strcmp(token, "r3") == 0 || 
    strcmp(token, "r4") == 0 || 
    strcmp(token, "r5") == 0 || 
    strcmp(token, "r6") == 0 || 
    strcmp(token, "r7") == 0) {
        cell->source_address = ADDR_MODE_REGISTER;
    }
    if (token[0] == '#') {
        validate_number(token);
        cell->source_address = ADDR_MODE_IMMEDIATE;
    }

    token = strtok(NULL, ",");
    if (token == NULL) {
        return;
    }
    if (strcmp(token, "r0") == 0 || 
    strcmp(token, "r1") == 0 || 
    strcmp(token, "r2") == 0 || 
    strcmp(token, "r3") == 0 || 
    strcmp(token, "r4") == 0 || 
    strcmp(token, "r5") == 0 || 
    strcmp(token, "r6") == 0 || 
    strcmp(token, "r7") == 0) {
        cell->dest_address = ADDR_MODE_REGISTER;
        return NULL;
    }
    if (token[0] == '#') {
        validate_number(token);
        cell->dest_address = ADDR_MODE_IMMEDIATE;
    }
}