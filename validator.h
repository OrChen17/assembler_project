#ifndef VALIDATOR
#define VALIDATOR
void validate_ascii_string(char *token);
void validate_number(char *token);
void validate_label(char *label);
void validate_opcode_operator_amount(int opcode, char *operator_1, char* operator_2);
#endif 
