/* In the second round of the assemble process the addresses in the symbols table are fixed (data lines are moved to the bottom).
Then the machine code cells with missing addresses (the ones that had a label as one of their operands) are populated with the proper values
It also verifies that entry and extern inputs were all valid labels (can only be done now, when the symbols table is full)*/

#include <stdio.h>
#include <string.h>
#include "label_fixer.h"
#include "symbol_table.h"
#include "machine_code.h"

void fix_labels() {
    fix_symbols_table();
    add_missing_addresses_code();
    check_all_entries_are_labels();
}

int check_all_entries_are_labels() {
    /*Verify that all of the EntryExtern cells contents are indeed labels*/
    entry_extern_cell_node* cur = get_ent_ext_section();
    while (cur != NULL)
    {
        if (cur->cell->label_type == LABEL_TYPE_ENTRY && is_label_in_symbol_list(cur->cell->label) == 0)
        {
            printf("ERROR: Entry %s is not a label\n", cur->cell->label);
            has_found_error = 1;
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}
void fix_symbols_table()
{
    /*Moving data rows to the bottom*/
    symbol_node* symbols;
    symbols = get_symbol_list();
    while (symbols != NULL)
    {
        if (symbols->symbol->type == DATA_SYMBOL)
        {
            symbols->symbol->address += IC;
        }
        symbols->symbol->address += 100;
    symbols = symbols->next;
    }
}

void add_missing_addresses_code()
{
    /*Adding addresses to code cells where missing*/
    code_cell_node* instructions;
    instructions = get_code_section();
    while (instructions != NULL)
    {
        if (strcmp(instructions->cell->address_needed, "") != 0)
        {
            instructions->cell->data = get_label_address(instructions->cell->address_needed);
            if (instructions->cell->data != -1)
            {
                strcpy(instructions->cell->address_needed, "");
                instructions->cell->encoding_type = ENCODING_TYPE_R;
                continue;
            }
            else if (get_label_type(instructions->cell->address_needed) == LABEL_TYPE_EXTERN)
            {
                instructions->cell->encoding_type = ENCODING_TYPE_E;
                instructions->cell->data = 0;
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
