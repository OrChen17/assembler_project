#ifndef VALIDATOR
#define VALIDATOR
void validate_ascii_string(char *token);
void validate_number(char *token);
void validate_label(char *label);
void validate_guidance_word(char* guidance_word);
void validate_guidance_input(char* guidance_word, char* guidance_input);
void validate_opcode_operator_amount(int opcode, char *operator_1, char* operator_2);
void validate_src_address_mode_for_opcode(int opcode, int address_mode);
void validate_dest_address_mode_for_opcode(int opcode, int address_mode);
#endif 
