#ifndef FILE_HANDLER
#define FILE_HANDLER

int assemble_file(FILE *pre_assembled_file);
/*runs the assembler on the file pointer*/

int is_empty_line(char *line);
/*Checks if the given line is all whitespaces 0 if it isn't empty, otherwise 1*/
#endif