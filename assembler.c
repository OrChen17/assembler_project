/* This program imitates an assembler - it can receive any number of files that contain assembly code
and assembles them (each separately) into machine language. It then converts the machine language into 
a special base-32 format */

/* This file is the first file in the processing chain.
 It is in charge of handling the input, calling the file_handler for each file and finally creating the output files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h>
#include <helper.h>
#include <output.h>
#include "unfold_macros.h"
#include "label_fixer.h"
#include "machine_code.h"


int process_file(char *filename)
/*Gets the name of the file without extension, unfolds the macros and writes the new content into a new file, 
and then runs the assembler on that new file. Eventually it creates the output files*/
{
    char* full_filename;
    char* full_filename_after_macros;
    FILE *pre_assembled_file;
    FILE *input_file;

    printf("Got File: %s\n\n", filename);
    full_filename = malloc(sizeof(char) * (strlen(filename) + strlen(".as") + 1));
    full_filename_after_macros = malloc(sizeof(char) * (strlen(filename) + strlen(".am") + 1));
    strcpy(full_filename, filename);
    strcat(full_filename, ".as");
    strcpy(full_filename_after_macros, filename);
    strcat(full_filename_after_macros, ".am");
    input_file = fopen(full_filename, "r");
    if (input_file == NULL) {
        printf("File %s was not found\n", full_filename);
        exit(1);
    }
    unfold_macros(full_filename_after_macros, input_file);
    pre_assembled_file = fopen(full_filename_after_macros, "r");
    if (pre_assembled_file == NULL) {
        printf("File %s was not found\n", full_filename_after_macros);
        exit(1);
    }
    
    assemble_file(pre_assembled_file); /*First round of the assemble process*/ 
    fix_labels(); /*Second round of the assemble process - fixing the symbols table and adding addresses where they are missing*/
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
    /*the entrypoint, handles the command line arguments*/
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