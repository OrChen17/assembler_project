/*the interface for the symbol table, which is implemented using a linked list*/
#include <helper.h>
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <machine_code.h>

symbol_node* symbol_list_start;
symbol_node* symbol_list_end;

void add_symbol(char* label, short int type) {
    Symbol *symbol = malloc(sizeof(Symbol));
    strcpy(symbol->label, label);
    symbol->type = type;
    if (type == CODE_SYMBOL) {
        /* Not sure - should this be the IC or IC + DC? */
        symbol->address = IC;
    }
    else {
        /* Not sure - should this be the DC or IC + DC? */
        symbol->address = DC;
    }

    if (symbol_list_start == NULL) {
        symbol_list_start = malloc(sizeof(symbol_node));
        strcpy(symbol->label, label);
        symbol_list_start->next = NULL;
        symbol_list_end = symbol_list_start;
    }
    else {
        symbol_list_end->next = malloc(sizeof(symbol_node));
        symbol_list_end->next->symbol = symbol;
        symbol_list_end->next->next = NULL;
        symbol_list_end = symbol_list_end->next;
    }
}

symbol_node* get_symbol_list() {
    return symbol_list_start;
}

int is_label_in_symbol_list(char* label) {
    symbol_node *cur = symbol_list_start;
    while (cur != NULL) {
        if (strcmp(cur->symbol->label, label) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}