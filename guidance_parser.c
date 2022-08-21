/*parses the Guiding Instructions into DataCells, and adds them to the cells list. */
#include "helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "machine_code.h"
#include "validator.h"
#include "symbol_table.h"
#include "guidance_parser.h"

int parse_guidance(GuidingInstruction *guidance) {
    int i;
    char* token;

    if (is_label_ext(guidance->label)) {
        printf("Error: Label %s is an external label.\n", guidance->label);
        has_found_error = 1;
        return 1;
    }
    
    if (strcmp(guidance->label, "") != 0)
    {
        add_symbol(guidance->label, DATA_SYMBOL);
    }
    if (trim_whitespace(guidance->guidance_input) == NULL || strcmp(trim_whitespace(guidance->guidance_input), "") == 0)
    {
        printf("Error: guidance input can't be empty\n");
        has_found_error = 1;
        return 1;
    }
    
    if (!strcmp(guidance->guidance_word, ".data"))
    {
        DataCell *data_cell = malloc(sizeof(DataCell));
        strcpy(data_cell->line_label, guidance->label);
        strcpy(data_cell->address_needed, "");
        validate_no_tracking_commas(guidance->guidance_input);
        token = strtok(guidance->guidance_input, " \t\n,");
        while (token != NULL)
        {
            validate_number_for_guidance(token);
            strcpy(data_cell->address_needed, "");
            data_cell->data = atoi(token);
            add_data(data_cell);
            token = strtok(NULL, " \t\n,");
            data_cell = malloc(sizeof(DataCell));
        }
    }
    else if (!strcmp(guidance->guidance_word, ".string"))
    {
        DataCell *data_cell = malloc(sizeof(DataCell));
        strcpy(data_cell->line_label, guidance->label);
        strcpy(data_cell->address_needed, "");
        token = trim_whitespace(guidance->guidance_input);
        validate_guidance_string_input(token);
        for (i = 1; i < strlen(token) - 1; i++) /*token[0] and token [length-1] are the " char, therefore the loope range is as defined here */
         {
            data_cell->data = token[i];
            add_data(data_cell);
            data_cell = malloc(sizeof(DataCell));
            strcpy(data_cell->address_needed, "");
        }
        data_cell = malloc(sizeof(DataCell));
        strcpy(data_cell->address_needed, "");
        data_cell->data = 0; /* Adding null terminator */
        add_data(data_cell);
    }
    else if (!strcmp(guidance->guidance_word, ".struct"))
    {
        DataCell *data_cell = malloc(sizeof(DataCell));
        strcpy(data_cell->line_label, guidance->label);
        strcpy(data_cell->address_needed, "");
        token = strtok(guidance->guidance_input, " \t,"); /* ##CR: we'll still have a problem in case of an only "," input */
        validate_number_for_guidance(token);
        data_cell->data = atoi(token);
        add_data(data_cell);
        token = strtok(NULL, " \t\n,");
        /* ##CR: I don't check for a series of commas */
        if (token == NULL)
        {
            printf("ERROR: struct guidance must have 2 inputs - 1 number and 1 string\n");
        }
        else
        {
            strcpy(token, trim_whitespace(token));
            validate_guidance_string_input(token);
            for (i = 1; i < strlen(token) - 1; i++) /* token[0] and token [length-1] are the " char */
            {
                data_cell = malloc(sizeof(DataCell));
                strcpy(data_cell->address_needed, "");
                data_cell->data = token[i];
                add_data(data_cell);
            }
            data_cell = malloc(sizeof(DataCell));
            strcpy(data_cell->address_needed, "");
            data_cell->data = 0;
            add_data(data_cell);
        }
    }
    else
    {
        EntryExternCell *entry_extern_cell = malloc(sizeof(EntryExternCell));
        strcpy(entry_extern_cell->label, trim_whitespace(guidance->guidance_input));
        validate_label(trim_whitespace(guidance->guidance_input));
        if (!strcmp(guidance->guidance_word, ".entry"))
        {
            entry_extern_cell->label_type = LABEL_TYPE_ENTRY;
        }
        else
        {
            if (is_label_in_symbol_list(guidance->guidance_input)) {
                printf("Error: label already defined can't be external %s\n", guidance->label);
                has_found_error = 1;
                return 1;
            }
            entry_extern_cell->label_type = LABEL_TYPE_EXTERN;
        }
        add_ent_ext(entry_extern_cell);
    }
    return 0;
}