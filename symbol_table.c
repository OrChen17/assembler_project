/*the interface for the symbol table, which is implemented using a linked list*/
#include <helper.h>
#include <stdio.h>
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <machine_code.h>

symbol_node* symbol_list_start;
symbol_node* symbol_list_end;

void add_symbol(char* label, short int type) {
    /*Adds the symbol label and type to the list. Some of the addresses will be fixed in the second pass. */
    /*We get here every time a label is detected in the assembled file*/
    Symbol *symbol = malloc(sizeof(Symbol));
    strcpy(symbol->label, label);
    symbol->type = type;
    if (type == CODE_SYMBOL) {
        symbol->address = IC;
    }
    else {
        symbol->address = DC;
    }

    if (symbol_list_start == NULL) {
        symbol_list_start = malloc(sizeof(symbol_node));
        symbol_list_start->symbol = symbol;
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
    /*Returns the head of the list*/
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

int get_label_address(char label[31])
/*To be used in the 2nd round for fixing code celss address*/
{
    symbol_node* cur = symbol_list_start;
    while (cur != NULL)
    {
        if (strcmp(cur->symbol->label, label) == 0)
        {
            return cur->symbol->address;
        }
    cur = cur->next;
    }
    return -1;
}

void free_symbols_table()
/*Freeing the allocated memory once the outputs are ready */
{
    symbol_node* symbols_start;
    symbol_node* to_free;
    
    symbols_start = get_symbol_list();
    if (symbols_start !=NULL)
    {
        to_free = symbols_start->next;
        free(symbols_start);
        symbol_list_start = NULL;
        symbol_list_end = NULL;
        if (to_free != NULL)
        {
            while (to_free->next != NULL)
            {
                free(to_free);
                to_free = to_free->next;
            }
        }
    }
}