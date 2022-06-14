#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#define DATA_SYMBOL 0
#define CODE_SYMBOL 1
#define ENTRY_SYMBOL 2
#define EXTERN_SYMBOL 3


typedef struct symbol {
    char *label;
    int address;
    short int type;
} Symbol;

typedef struct sym_node {
    Symbol* symbol;
    struct sym_node * next;
} symbol_node;

void add_symbol(char* label, short int type);
symbol_node* get_symbol_list();
int is_label_in_symbol_list(char* label);
#endif