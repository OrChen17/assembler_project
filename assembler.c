#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h>
#include <helper.h>
#include <output.h>
#include "unfold_macros.h"


int process_file(char *filename) 
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
    /* TODO Eran- 2nd iteration */
    if (has_found_error) {
        printf("\nFound error, assembler failed\n");
        exit(1);
    }

    create_output_files(filename);
    free(full_filename);
    free(full_filename_after_macros);
    fclose(input_file);
    fclose(pre_assembled_file);
    return 1;
}



int main(int argc, char *argv[]) {
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