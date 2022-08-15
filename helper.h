#ifndef HELPER
#define HELPER

int has_found_error;
#define CELL_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c"
#define CELL_TO_BINARY(opcode, s_addr, d_addr, enc_type)  \
  (opcode & 0x08 ? '1' : '0'), \
  (opcode & 0x04 ? '1' : '0'), \
  (opcode & 0x02 ? '1' : '0'), \
  (opcode & 0x01 ? '1' : '0'), \
  (s_addr & 0x02 ? '1' : '0'), \
  (s_addr & 0x01 ? '1' : '0'), \
  (d_addr & 0x02 ? '1' : '0'), \
  (d_addr & 0x01 ? '1' : '0'), \
  (enc_type & 0x02 ? '1' : '0'), \
  (enc_type & 0x01 ? '1' : '0')


#define OPCODE_MOV 0
#define OPCODE_CMP 1
#define OPCODE_ADD 2
#define OPCODE_SUB 3
#define OPCODE_NOT 4
#define OPCODE_CLR 5
#define OPCODE_LEA 6
#define OPCODE_INC 7
#define OPCODE_DEC 8
#define OPCODE_JMP 9
#define OPCODE_BNE 10
#define OPCODE_GET 11
#define OPCODE_PRN 12
#define OPCODE_JSR 13
#define OPCODE_RTS 14
#define OPCODE_HLT 15

#define ADDR_MODE_IMMEDIATE 0
#define ADDR_MODE_DIRECT 1
#define ADDR_MODE_DIRECT_PARAM 2
#define ADDR_MODE_REGISTER 3

#define ENCODING_TYPE_A 0;
#define ENCODING_TYPE_E 1;
#define ENCODING_TYPE_R 2;

#define LABEL_TYPE_ENTRY 0;
#define LABEL_TYPE_EXTERN 1;

typedef struct macro {
    char name[20];
    char content[500];
} MacroCell;

typedef struct machine_code_cell {
    unsigned opcode:4;
    unsigned source_address:2;
    unsigned dest_address:2;
    unsigned encoding_type:2;
} HeaderCodeCell;

typedef struct data_instruction {
    char label[31];
    char opcode[10];
    char operand_1[40];
    char operand_2[40];
    /* We limit lines to be of length 83 but here we give them an accumulated length of 121 */
} DataInstruction; /* Bad name! */


typedef struct guiding_instruction {
    char label[31];
    char guidance_word[8];
    char guidance_input[200]; /* Probably should be dynamic */
} GuidingInstruction;

typedef struct instruction_cell {
    signed data:8;
    unsigned encoding_type:2;
    char address_needed[31];
} CodeCell;

typedef struct guiding_cell {
    signed data:10;
    char address_needed[31];
} DataCell;

typedef struct entry_extern_cell{
    char label[31];
    int label_type;
} EntryExternCell;

/*typedef struct extern_cell {
    char label[31];
} ExternCell;*/
  
char* machine_code_cell_to_string(struct machine_code_cell *cell);
/*Translates Machine Code Cell to a string, for printing*/
char *trim_whitespace(char *str);
/*trim the whitespace of the given str*/
char* code_cell_to_b32(CodeCell *code_cell);
/*transforms the code cell to b32*/
char* int_to_base_32(int data);
/*converts given data to base 32*/
CodeCell* header_code_cell_to_code_cell(HeaderCodeCell *header_code_cell);
/*converts a header code cell to a regular code cell*/
#endif
