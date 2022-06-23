#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h>
#include <helper.h>
#include <output.h>
#include "unfold_macros.h"


int process_file(char *filename) 
{
    printf("Got File: %s\n", filename);
    char* full_filename = malloc(sizeof(char) * (strlen(filename) + strlen(".as") + 1));
    strcpy(full_filename, filename);
    strcat(full_filename, ".as");
    FILE *input_file = fopen(full_filename, "r");
    if (input_file == NULL) {
        printf("File %s was not found\n", full_filename);
        exit(1);
    }
    free(full_filename);
    FILE *pre_assembled_file = unfold_macros(input_file);
    // Maybe here we need to "rewind" to the beginning of the file?
    /*assemble_file(pre_assembled_file);*/ //maybe first use fopen on preassembled file?
    // TODO Eran- 2nd iteration
    if (has_found_error) {
        printf("Found error, assembler failed\n");
        exit(1);
    }
    /*create_output_files(filename);*/
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