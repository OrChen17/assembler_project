#include <stdio.h>
#include "helper.h"

typedef struct node {
    MacroCell* cell;
    struct node *next;
} macro_cell_node;

FILE* unfold_macros(FILE *input_file);
void add_macro_to_macros_table(MacroCell * cell);
int not_in_macros_table(char* token);
/*char* unfold_single_macro(char * token);*/
void free_macros_list(macro_cell_node* start);