#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h>
#include <helper.h>
#include <output.h>


int process_file(char *filename) 
{
    printf("Got File: %s\n", filename);
    filename = strcat(filename, ".as");
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("File %s was not found\n", filename);
        exit(1);
    }
    assemble_file(input_file);
    if (has_found_error) {
        printf("Found error, assembler failed\n");
        exit(1);
    }
    create_output_files(filename);
    return 1;
}



int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No files detected, please specify file names\n");
        exit(1);
    }
    for (int i = 1; i< argc; i++) {
        process_file(argv[i]);
    }
}