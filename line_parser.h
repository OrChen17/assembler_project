#ifndef LINE_PARSER
#define LINE_PARSER

int parse_instruction_line(char *line);
int parse_guiding_line(char *line);
DataGuiding* parse_guiding_line_to_struct(char* line);
#endif