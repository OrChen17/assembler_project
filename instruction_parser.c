#include <helper.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <machine_code.h>
#include <validator.h>
#include <symbol_table.h>

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
        has_found_error = 1;
        return -1;
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
        has_found_error = 1;
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

void get_address_cell(char* operand_1, int src_addr_mode, char* operand_2, int dest_addr_mode, CodeCell* cells) {
    char* label;
    char* num;
    if (operand_1 != NULL) {
        if (src_addr_mode == ADDR_MODE_IMMEDIATE) {
            strcpy(cells[0].label_needed, "");
            cells[0].encoding_type = ENCODING_TYPE_A;
            cells[0].data = atoi(operand_1 + 1);
        }
        if (src_addr_mode == ADDR_MODE_DIRECT) {
            strcpy(cells[0].label_needed, operand_1);
        }
        if (src_addr_mode == ADDR_MODE_DIRECT_PARAM) {
            label = strtok(operand_1, ".");
            strcpy(cells[0].label_needed, label);
            num = strtok(NULL, "");
            strcpy(cells[1].label_needed, "");
            cells[1].data = atoi(num);
            cells[1].encoding_type = ENCODING_TYPE_A;
        }
        if (src_addr_mode == ADDR_MODE_REGISTER) {
            int data = atoi(operand_1 + 1);
            data = data << 4;
            if (dest_addr_mode == ADDR_MODE_REGISTER) {
                data = data | atoi(operand_2 + 1);
            }
            strcpy(cells[0].label_needed, "");
            cells[0].data = data;
            cells[0].encoding_type = ENCODING_TYPE_A;
        }
    }

    if (operand_2 != NULL) {
        char* label;
        char* num;
        if (dest_addr_mode == ADDR_MODE_IMMEDIATE) {
            strcpy(cells[2].label_needed, "");
            cells[2].encoding_type = ENCODING_TYPE_A;
            cells[2].data = atoi(operand_2 + 1);
        }
        if (dest_addr_mode == ADDR_MODE_DIRECT) {
            strcpy(cells[2].label_needed, operand_2);
        }
        if (dest_addr_mode == ADDR_MODE_DIRECT_PARAM) {
            label = strtok(operand_2, ".");
            strcpy(cells[2].label_needed, label);
            num = strtok(NULL, "");
            strcpy(cells[3].label_needed, "");
            cells[3].data = atoi(num);
            cells[3].encoding_type = ENCODING_TYPE_A;
        }
        if (dest_addr_mode == ADDR_MODE_REGISTER) {
            if (src_addr_mode != ADDR_MODE_REGISTER) {
                strcpy(cells[2].label_needed, "");
                cells[2].encoding_type = ENCODING_TYPE_A;
                cells[2].data = atoi(operand_2 + 1);
            }
        }
    }
}

int parse_instruction(DataInstruction *instruction) {
    int i;
    CodeCell *cells;
    HeaderCodeCell *cell = malloc(sizeof(HeaderCodeCell)); /* CR - Need to free memory at some point */

    cell->encoding_type = ENCODING_TYPE_A;
    cell->opcode = parse_opcode(cell, instruction);
    if (cell->opcode == -1) {
        return 1;
    }
    validate_opcode_operator_amount(cell->opcode, instruction->operand_1, instruction->operand_2);
    add_symbol(instruction->label, CODE_SYMBOL);


    cell->source_address = parse_addr_mode(cell, instruction, instruction->operand_1);
    cell->dest_address = parse_addr_mode(cell, instruction, instruction->operand_2);
    printf("Cell: opcode=%d source_address=%d dest_address=%d\n", cell->opcode, cell->source_address, cell->dest_address);
    if (instruction->operand_2 != NULL) {
        validate_src_address_mode_for_opcode(cell->opcode, cell->source_address);
        validate_dest_address_mode_for_opcode(cell->opcode, cell->dest_address);
    }
    else {
        validate_dest_address_mode_for_opcode(cell->opcode, cell->source_address);
    }

    
    add_code(header_code_cell_to_code_cell(cell));

    cells = malloc(sizeof(CodeCell) * 4); /* CR - Need to free memory at some point */
    for (i = 0; i < 4; i++) {
        strcpy(cells[i].label_needed, "1NULL");
        cells[i].encoding_type = 0;
        cells[i].data = 0;
    }
    get_address_cell(instruction->operand_1, cell->source_address, instruction->operand_2, cell->dest_address, cells);

    for (i = 0; i < 4; i++) {
        if (strcmp(cells[i].label_needed, "1NULL") == 0) {
            continue;
        }
        printf("Adding address cell: data=%d, label_needed=%s, encoding_type=%d \n", cells[i].data, cells[i].label_needed, cells[i].encoding_type);
        add_code(&cells[i]);
    }
    return 0;
}