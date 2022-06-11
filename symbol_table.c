#include <helper.h>
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <machine_code.h>

symbol_node* symbol_list;

void add_symbol(char* label, short int type) {
    Symbol *symbol = malloc(sizeof(Symbol));
    symbol->label = label;
    symbol->type = type;
    if (type == CODE_SYMBOL) {
        // Not sure - should this be the IC or IC + DC?
        symbol->address = IC;
    }
    else {
        // Not sure - should this be the DC or IC + DC?
        symbol->address = DC;
    }

    if (symbol_list == NULL) {
        symbol_list = malloc(sizeof(symbol_node));
        symbol_list->symbol = symbol;
        symbol_list->next = NULL;
    }
    else {
        symbol_node *cur = symbol_list;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(symbol_node));
        cur->next->symbol = symbol;
        cur->next->next = NULL;
    }
}

symbol_node* get_symbol_list() {
    return symbol_list;
}

int is_label_in_symbol_list(char* label) {
    symbol_node *cur = symbol_list;
    while (cur != NULL) {
        if (strcmp(cur->symbol->label, label) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}