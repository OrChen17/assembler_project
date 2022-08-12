/* This file is the first file in the processing chain.
 in charge of handling the input, calling the file_handler for each file and finally calling the output */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h>
#include <helper.h>
#include <output.h>
#include "unfold_macros.h"
#include "label_fixer.h"


int process_file(char *filename)
/*Gets the name of the file without extension. runs the assembler on the file*/
{
    char* full_filename;
    char* full_filename_after_macros;
    FILE *pre_assembled_file;
    FILE *input_file;
    printf("Got File: %s\n\n", filename);
    full_filename = malloc(sizeof(char) * (strlen(filename) + strlen(".as") + 1));
    full_filename_after_macros = malloc(sizeof(char) * strlen(PRE_ASSEMBLED_FILE_NAME) + 1);
    strcpy(full_filename, filename);
    strcat(full_filename, ".as");
    input_file = fopen(full_filename, "r");
    if (input_file == NULL) {
        printf("File %s was not found\n", full_filename);
        exit(1);
    }

    strcpy(full_filename_after_macros, unfold_macros(input_file));
    pre_assembled_file = fopen(full_filename_after_macros, "r");
    if (pre_assembled_file == NULL) {
        printf("File %s was not found\n", full_filename_after_macros);
        exit(1);
    }

    assemble_file(pre_assembled_file);
    fix_labels();
    
    if (has_found_error) {
        printf("\nFound error, assembler failed\n");
        exit(1);
    }

    create_output_files(filename);
    free(full_filename);
    free(full_filename_after_macros);
    /*fclose(input_file);*/
    /* For some reason closing the file leads to a crash */
    fclose(pre_assembled_file);
    return 1;
}



int main(int argc, char *argv[]) {
    /*the entrypoint, handles the arguments*/
    int i;
    if (argc == 1) {
        printf("No files detected, please specify file names\n");
        exit(1);
    }
    for (i = 1; i< argc; i++) {
        process_file(argv[i]);
    }
    return 0;
}