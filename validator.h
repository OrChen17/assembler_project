#ifndef VALIDATOR
#define VALIDATOR
void validate_ascii_string(char *token);
/* validates the token is proper ascii*/
void validate_number(char *token);
/* validates the token is proper number*/
void validate_label(char *label);
/* validates the string is a valid label */
void check_duplicate_label(char *label);
/* validates that the label is not already in the symbols table (duplicates are not allowed) */
void validate_guidance_word(char* guidance_word);
/* validates the string is proper guiding word*/

void validate_no_tracking_commas(char guidance_input[200]);
/* validates there are no tracking commas, including spaces*/
void validate_number_for_guidance(char* token);
/* validates input is a number */ 
void validate_guidance_string_input(char* token);
/* validates string guiding input is correct*/
/*void validate_guidance_struct_input(char* token);*/

void validate_opcode_operator_amount(int opcode, char *operator_1, char* operator_2);
/* validates the amount of operators is valid for the opcode*/

void validate_src_address_mode_for_opcode(int opcode, int address_mode);
/* validates the src address mode is valid for the opcode*/

void validate_dest_address_mode_for_opcode(int opcode, int address_mode);
/* validates the dest address mode is valid for the opcode*/

#endif 
