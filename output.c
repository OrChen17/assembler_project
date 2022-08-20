/*outputs the required files, by using the code_section and data_section. */

#include <stdlib.h>
#include <stdio.h>
#include <machine_code.h>
#include <helper.h>
#include <string.h>
#include <symbol_table.h>
#include <label_fixer.h>

void create_object_file(char *file_name)
{
    FILE *output_file;
    FILE *extern_output_file;
    FILE *entry_output_file;
    char *extern_output_filename;
    char *entry_output_filename;
    char *output_filename;
    char *total_instructions;
    char *total_data;
    int start_index;
    code_cell_node *instructions;
    data_cell_node *data;
    int i;
    int first_extern_symbol = 0;
    int first_entry_symbol = 0;
    output_filename = strcat(file_name, ".ob");
    printf("\nMaking output file %s\n", output_filename);
    output_file = fopen(output_filename, "w");
    start_index = 100;
    instructions = get_code_section();
    i = 0;
    total_instructions = int_to_base_32(IC);
    if (total_instructions[0] == '!') {
        total_instructions += 1;
    }
    total_data = int_to_base_32(DC);
    if (total_data[0] == '!') {
        total_data += 1;
    }
    fprintf(output_file, "%s %s\n", total_instructions, total_data);
    while (instructions != NULL)
    {
        int line_index = start_index + i;
        char *cell_base32 = code_cell_to_b32(instructions->cell);
        char *index_base32 = int_to_base_32(line_index);
        fprintf(output_file, "%s %s\n", index_base32, cell_base32);

        if (strcmp(instructions->cell->address_needed, "") != 0 && get_label_type(instructions->cell->address_needed) == LABEL_TYPE_EXTERN)
        {
            if (first_extern_symbol == 0) {
                first_extern_symbol = 1;
                file_name = strtok(file_name, ".");
                extern_output_filename = strcat(file_name, ".ext");
                printf("\nMaking extern file %s\n", extern_output_filename);
                extern_output_file = fopen(extern_output_filename, "w");
            }
            fprintf(extern_output_file, "%s %s\n", instructions->cell->address_needed, index_base32);
        }
        if (strcmp(instructions->cell->line_label, "") != 0 && get_label_type(instructions->cell->line_label) == LABEL_TYPE_ENTRY)
        {
            if (first_entry_symbol == 0) {
                first_entry_symbol = 1;
                file_name = strtok(file_name, ".");
                entry_output_filename = strcat(file_name, ".ent");
                printf("\nMaking entry file %s\n", entry_output_filename);
                entry_output_file = fopen(entry_output_filename, "w");
            }
            fprintf(entry_output_file, "%s %s\n", instructions->cell->line_label, index_base32);
        }
        instructions = instructions->next;
        i++;
    }

    data = get_data_section();
    while (data != NULL)
    {
        int line_index = start_index + i;
        char *cell_base32 = int_to_base_32(data->cell->data);
        char *index_base32 = int_to_base_32(line_index);
        fprintf(output_file, "%s %s\n", index_base32, cell_base32);
        if (strcmp(data->cell->line_label, "") != 0 && get_label_type(data->cell->line_label) == LABEL_TYPE_ENTRY)
        {
            if (first_entry_symbol == 0) {
                first_entry_symbol = 1;
                file_name = strtok(file_name, ".");
                entry_output_filename = strcat(file_name, ".ent");
                printf("\nMaking entry file %s\n", entry_output_filename);
                entry_output_file = fopen(entry_output_filename, "w");
            }
            fprintf(entry_output_file, "%s %s\n", data->cell->line_label, index_base32);
        }
        data = data->next;
        i++;
    }
}


void create_output_files(char *file_name)
{
    create_object_file(file_name);
}