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
    int start_index;
    code_cell_node *instructions;
    int i;
    char *file_name_tmp = malloc(sizeof(char) * (strlen(file_name) + 1));
    strcpy(file_name_tmp, file_name);
    output_filename = strcat(file_name_tmp, ".ob");
    strcpy(file_name_tmp, file_name);
    printf("\nMaking output file %s\n", output_filename);
    output_file = fopen(output_filename, "w");
    extern_output_filename = strcat(file_name_tmp, ".ext");
    strcpy(file_name_tmp, file_name);

    extern_output_file = fopen(extern_output_filename, "w");
    entry_output_filename = strcat(file_name_tmp, ".ent");
    strcpy(file_name_tmp, file_name);
    entry_output_file = fopen(entry_output_filename, "w");
    start_index = 100;
    instructions = get_code_section();
    i = 0;
    fprintf(output_file, "%s %s\n", int_to_base_32(IC), int_to_base_32(DC));
    while (instructions != NULL)
    {
        int line_index = start_index + i;
        char *cell_base32 = code_cell_to_b32(instructions->cell);
        char *index_base32 = int_to_base_32(line_index);
        fprintf(output_file, "%s %s\n", index_base32, cell_base32);

        if (strcmp(instructions->cell->address_needed, "") != 0 && get_label_type(instructions->cell->address_needed) == LABEL_TYPE_EXTERN)
        {
            fprintf(extern_output_file, "%s %s\n", instructions->cell->address_needed, index_base32);
        }
        if (strcmp(instructions->cell->line_label, "") != 0 && get_label_type(instructions->cell->line_label) == LABEL_TYPE_ENTRY)
        {
            fprintf(entry_output_file, "%s %s\n", instructions->cell->line_label, index_base32);
        }
        instructions = instructions->next;
        i++;
    }
}


void create_output_files(char *file_name)
{
    create_object_file(file_name);
}