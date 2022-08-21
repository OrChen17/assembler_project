#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#define DATA_SYMBOL 0
#define CODE_SYMBOL 1
#define ENTRY_SYMBOL 2
#define EXTERN_SYMBOL 3


typedef struct symbol {
    char label[31];
    int address;
    short int type;
} Symbol;

typedef struct sym_node {
    Symbol* symbol;
    struct sym_node * next;
} symbol_node;

void free_symbols_table();
/*Freeing the allocated memory once the outputs are ready */

void add_symbol(char* label, short int type);
/*Adds the symbol label and type to the list. Some of the addresses will be fixed in the second pass. */
symbol_node* get_symbol_list();
/*Returns the head of the list*/
int is_label_in_symbol_list(char* label);
int get_label_address(char label[31]);
/*To be used in the 2nd round for fixing code celss address*/
#endif