#ifndef LINE_PARSER
#define LINE_PARSER

int parse_instruction_line(char *line);
/*Parses a DataInstruction from a given line*/
int parse_guiding_line(char *line);
/*Parses a guiding line into a GuidanceInstruction*/
#endif
