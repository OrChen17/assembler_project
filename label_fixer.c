#include <stdio.h>
#include <string.h>
#include "label_fixer.h"
#include "symbol_table.h"
#include "machine_code.h"

void fix_labels() {
    /*symbol_node* symbols = get_symbol_list();
    while (symbols != NULL)
    {
        printf("ADDRESS BEFORE FIX: %d\n", symbols->symbol->address);
        symbols = symbols->next;
    }*/
    fix_symbols_table();
    add_missing_addresses_code();
    check_all_entries_are_labels();
    /* add_missing_addresses_data(); */
}
void check_all_entries_are_labels() {
    entry_extern_cell_node* cur = get_ent_ext_section();
    while (cur != NULL)
    {
        if (is_label_in_symbol_list(cur->cell->label) == 0)
        {
            printf("ERROR: Entry %s is not a label\n", cur->cell->label);
            has_found_error = 1;
        }
        cur = cur->next;
    }
}
void fix_symbols_table()
{
    symbol_node* symbols;
    symbols = get_symbol_list();
    printf("\n");
    while (symbols != NULL)
    {
        /*printf("\nLabel before fix: %s\n", symbols->symbol->label);
        printf("Address before fix: %d\n", symbols->symbol->address);*/
        symbols = symbols->next;
    }
    printf("\n************************\n");
    symbols = get_symbol_list();


    while (symbols != NULL)
    {
        if (symbols->symbol->type == DATA_SYMBOL)
        {
            symbols->symbol->address += IC;
        }
        symbols->symbol->address += 100;
   /* printf("\nLabel after fix: %s\n", symbols->symbol->label);
    printf("Address after fix: %d\n", symbols->symbol->address);*/
    symbols = symbols->next;
    }
}

void add_missing_addresses_code()
{
    code_cell_node* instructions;
    instructions = get_code_section();
    while (instructions != NULL)
    {
        /*printf("@@ %s\n", instructions->cell->address_needed);*/
        if (strcmp(instructions->cell->address_needed, "") != 0)
        {
            /*printf("Adding missing address cell: data=%d, encoding_type=%d \n", instructions->cell->data, instructions->cell->encoding_type); */
            instructions->cell->data = get_label_address(instructions->cell->address_needed);
            if (instructions->cell->data != -1)
            {
                strcpy(instructions->cell->address_needed, "");
                instructions->cell->encoding_type = ENCODING_TYPE_R;
                /*printf("Added missing address cell: data=%d, encoding_type=%d \n", instructions->cell->data, instructions->cell->encoding_type);*/
                continue;
            }
            else if (get_label_type(instructions->cell->address_needed) == LABEL_TYPE_EXTERN)
            {
                instructions->cell->encoding_type = ENCODING_TYPE_E;
                instructions->cell->data = 0; /* I think that for externs the address should be 0 */
                /*printf("Added missing address cell: data=%d, encoding_type=%d \n", instructions->cell->data, instructions->cell->encoding_type);*/
            }
            else
            {
                printf("Illegal label operand %s. This label does not exist\n", instructions->cell->address_needed);
                has_found_error = 1;
            }
        }
    instructions = instructions->next;
    }
}

int get_label_type(char label[31])
{
    entry_extern_cell_node* ent_exts;
    ent_exts = get_ent_ext_section();
    while (ent_exts != NULL)
    {
        if (strcmp(label, ent_exts->cell->label) == 0)
        {
            return ent_exts->cell->label_type;
        }
        ent_exts = ent_exts->next;
    }
    return -1;
}
