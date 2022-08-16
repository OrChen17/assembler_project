#include <stdio.h>
#include "helper.h"
#define PRE_ASSEMBLED_FILE_NAME "pre_assembled_file.am" /* Maybe the name should be identical to the 
input file's name, only with .am instead of .as */

typedef struct node {
    char name[20];
    char content[500];
    struct node *next;
} macro_cell_node;

char* unfold_macros(FILE *input_file);
void add_macro_to_macros_table(MacroCell * cell);
int not_in_macros_table(char* token);
char* unfold_single_macro(char* token);
void free_macros_list(macro_cell_node* start);