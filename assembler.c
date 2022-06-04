#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <file_handler.h>

int process_file(char *filename) {
    printf("Got File: %s\n", filename);
    filename = strcat(filename, ".as");
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("File %s was not found\n", filename);
        exit(1);
    }
    assemble_file(input_file);
    return 1;
}



int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No files detected, please specify file names\n");
        exit(1);
    }
    for (int i = 1; i<= argc; i++) {
        process_file(argv[i]);
    }
}