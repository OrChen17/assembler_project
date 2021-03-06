#include "helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "machine_code.h"
#include "validator.h"
#include "symbol_table.h"
#include "guidance_parser.h"

int parse_guidance(DataGuiding *guidance) {
    int i;
    char* token;
    DataCell *data_cell = malloc(sizeof(DataCell));
    /* Might need guidance_tokenized to avoid corruption */
    validate_guidance_input(guidance->guidance_word, guidance->guidance_input);
    if (strcmp(guidance->guidance_word, ".data"))
    {
        add_symbol(guidance->label, DATA_SYMBOL);
        strcpy(data_cell->label_needed, guidance->label);
        /* Is label auto-initialized with a null value? */
        /* Do I need to put null values in label for the following numbers? */
        token = strtok(guidance->guidance_input, " \t,");
        while (token != NULL)
        {
            data_cell->data = atoi(token);
            add_data(data_cell);
            token = strtok(NULL, " \t,");
        }
    }
    else if (strcmp(guidance->guidance_word, ".string"))
    {
        add_symbol(guidance->label, DATA_SYMBOL);
        strcpy(data_cell->label_needed, guidance->label);
        token = trim_whitespace(guidance->guidance_input);
        for (i = 1; i < strlen(token) - 1; i++) /*token[0] and token [length-1] are the " char */
         {
            data_cell->data = token[i] + '0';
            add_data(data_cell);
        }
        data_cell->data = 0;
        add_data(data_cell);
    }
    else if (strcmp(guidance->guidance_word, ".struct"))
    {
        add_symbol(guidance->label, DATA_SYMBOL);
        strcpy(data_cell->label_needed, guidance->label);
        token = trim_whitespace(strtok(guidance->guidance_input, ","));
        data_cell->data = atoi(token);
        add_data(data_cell);

        token = trim_whitespace(strtok(NULL, " \t"));
        for (i = 1; i < strlen(token) - 1; i++) /*token[0] and token [length-1] are the " char */
         {
            data_cell->data = token[i] + '0';
            add_data(data_cell);
        }
        data_cell->data = 0;
        add_data(data_cell);
    }
    /* else if entry or extern --> add relevant symbpl; put into files. Here or not here? */
    return 0;
}