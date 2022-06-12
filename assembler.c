#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h> /* won't complie in Ubuntu. For local headers it requires " " instead of <> */


int process_file(char *filename) {
    FILE *pre_assembled_file;
    FILE *input_file;
    printf("Got File: %s\n", filename);
    filename = strcat(filename, ".as");
    input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("File %s was not found\n", filename);
        exit(1);
    }
    /* pre_assembled_file = pre_assemble_file(input_file) 
    TODO - declare and write the pre_assemble_file function */
    /* get machine language "table" from 1st assemble round and a symbols table
    Then send the above as inputs to ths 2nd assembling function */
    assemble_file(pre_assembled_file);
    return 1;
}



int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No files detected, please specify file names\n");
        exit(1);
    }
    /* ##CR: we need a pre-assemble phase for deploying macros */
    for (int i = 1; i< argc; i++) {
        process_file(argv[i]);
    }
}