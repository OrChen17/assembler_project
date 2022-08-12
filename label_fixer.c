#include <stdio.h>
#include <string.h>
#include "label_fixer.h"
#include "symbol_table.h"
#include "machine_code.h"

void fix_labels() {
    fix_symbols_table();
    add_missing_addresses_code();
    /* add_missing_addresses_data(); */
}

void fix_symbols_table()
{
    symbol_node* symbols;
    symbols = get_symbol_list();
    while (symbols != NULL)
    {
        if (symbols->symbol->type == DATA_SYMBOL)
        {
            symbols->symbol->address += IC;
        }
    symbols = symbols->next;
    }
}

void add_missing_addresses_code()
{
    code_cell_node* instructions;
    instructions = get_code_section();
    printf("\n\n");
    while (instructions != NULL)
    {
        if (strcmp(instructions->cell->label_needed, "") != 0)
        {
            printf("Adding missing address cell: data=%d, encoding_type=%d \n", instructions->cell->data, instructions->cell->encoding_type);
            instructions->cell->encoding_type = ENCODING_TYPE_R;
            instructions->cell->data = get_label_address(instructions->cell->label_needed);
            printf("Added missing address cell: data=%d, encoding_type=%d \n", instructions->cell->data, instructions->cell->encoding_type);
        }
    instructions = instructions->next;
    }
}