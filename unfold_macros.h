#include <stdio.h>
#include "helper.h"

/*defining the macros linked list*/
typedef struct node {
    char name[20];
    char content[500];
    struct node *next;
} macro_cell_node;

void unfold_macros(char *full_filename_after_macros, FILE *input_file);
/*Goes through the original input file and copies the rows as they are into a new file, unless
the line read starts with the word macro, or contains a macro's name. In the first case it adds the macro's name and contents
into a linked list; in the second case it goes to the list and brings the content, replacing the macro's name with its contents.
The new file that's created is identical to the original file, only with macros unfolded
We assume that macros have no errors in them, as requeted in the excercise*/
void add_macro_to_macros_table(MacroCell * cell);
/*Adds a detected macro into the linked list*/
int not_in_macros_table(char* token);
/*Checks if a certain object is a macro*/
char* unfold_single_macro(char* token);
/*When detecting a macro's name in the original input file, the code comes here in order to look for the
macro's content and write them into the right place in the new file*/
void free_macros_table();