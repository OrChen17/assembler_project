#ifndef LINE_PARSER
#define LINE_PARSER

int parse_instruction_line(char *instruction_to_parse);
/*Parses an instruction lint into an InstructionComponent*/
int parse_guiding_line(char *guidance_to_parse);
/*Parses a guiding line into a GuidanceInstruction*/
#endif
