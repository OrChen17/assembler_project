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
    DataCell *data_cell = malloc(sizeof(DataCell));
    EntryExternCell *entry_extern_cell = malloc(sizeof(EntryExternCell));
    
    /* Might need to wrap with: if validate_guidance_input, only then do all the parsing */
    validate_guidance_input(guidance->guidance_word, guidance->guidance_input);

    if (strcmp(guidance->label, "") != 0)
    {
        add_symbol(guidance->label, DATA_SYMBOL);
    }

    
    if (!strcmp(guidance->guidance_word, ".data"))
    {
        strcpy(data_cell->address_needed, "");
        /* Do I need to put null values in label for the following numbers? */
        /* Not sure what this comment means ^^ */
        token = strtok(guidance->guidance_input, " \t,");
        while (token != NULL)
        {
            data_cell = malloc(sizeof(DataCell));
            data_cell->data = atoi(token);
            add_data(data_cell);
            token = strtok(NULL, " \t,");
        }
    }
    else if (!strcmp(guidance->guidance_word, ".string"))
    {
        strcpy(data_cell->address_needed, "");
        token = trim_whitespace(guidance->guidance_input);
        for (i = 1; i < strlen(token) - 1; i++) /*token[0] and token [length-1] are the " char, therefore the loope range is as defined here */
         {
            data_cell = malloc(sizeof(DataCell));
            data_cell->data = token[i];
            printf("@#@# %d\n", data_cell->data);
            add_data(data_cell);
        }
        data_cell->data = 0; /* Adding null terminator */
        add_data(data_cell);
    }
    else if (!strcmp(guidance->guidance_word, ".struct"))
    {
        strcpy(data_cell->address_needed, "");
        token = trim_whitespace(strtok(guidance->guidance_input, " \t,"));
        data_cell = malloc(sizeof(DataCell));
        data_cell->data = atoi(token);
        add_data(data_cell);
        token = strtok(NULL, " \t\n");
        strcpy(token, trim_whitespace(token));
        for (i = 1; i < strlen(token) - 1; i++) /* token[0] and token [length-1] are the " char */
        {
            data_cell->data = token[i] + '0';
            add_data(data_cell);
        }
        data_cell->data = 0;
        add_data(data_cell);
    }
    else
    {
        strcpy(entry_extern_cell->label, trim_whitespace(guidance->guidance_input));
        if (!strcmp(guidance->guidance_word, ".entry"))
        {
            entry_extern_cell->label_type = LABEL_TYPE_ENTRY;
        }
        else
        {
            entry_extern_cell->label_type = LABEL_TYPE_EXTERN;
        }
        add_ent_ext(entry_extern_cell);
    }
    return 0;
}