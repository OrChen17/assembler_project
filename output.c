#include <stdlib.h>
#include <stdio.h>
#include <machine_code.h>
#include <helper.h>
#include <string.h>

void create_object_file(char* file_name) {
    FILE *output_file;
    int start_index;
    code_cell_node* instructions;
    int i;
    char* output_filename = strcat(file_name, ".ob");
    printf("\nMaking output file %s\n", output_filename);
    output_file = fopen(output_filename, "w");
    start_index = 100;
    instructions = get_code_section();
    i = 0;
    fprintf(output_file, "%s %s\n", int_to_base_32(IC), int_to_base_32(DC));
    while(instructions != NULL) {
        int line_index = start_index + i;
        char* cell_base32 = code_cell_to_b32(instructions->cell);
        char* index_base32 = int_to_base_32(line_index);
        fprintf(output_file, "%s %s\n",index_base32, cell_base32);
        instructions = instructions->next;
        i++;
    }
}

void create_output_files(char* file_name) {
    create_object_file(file_name);
}