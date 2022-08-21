#include <stdio.h>
#include "helper.h"

typedef struct node {
    char name[20];
    char content[500];
    struct node *next;
} macro_cell_node;

void unfold_macros(char *full_filename_after_macros, FILE *input_file);
void add_macro_to_macros_table(MacroCell * cell);
int not_in_macros_table(char* token);
char* unfold_single_macro(char* token);
void free_macros_list(macro_cell_node* start);