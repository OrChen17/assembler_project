#include <stdlib.h>
#include <stdio.h>
#include <machine_code.h>
#include <helper.h>
#include <string.h>

void create_object_file(char* file_name) {
    char* output_filename = strcat(file_name, ".ob");
    FILE *output_file = fopen(output_filename, "w");
    int start_index = 100;
    node_t* instructions = get_code_section();
    int i = 0;
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