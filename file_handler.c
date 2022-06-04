
#include <stdio.h>
#include <stdlib.h>
#include <file_handler.h>

int assemble_file(FILE *input_file) {
    char line[83];
    while (fgets(line, 83, input_file)) {
        printf("%s\n", line);
    }
}