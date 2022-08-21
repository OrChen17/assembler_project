#ifndef MACHINE_CODE
#define MACHINE_CODE
#include <helper.h>

typedef struct instruction_node {
    CodeCell* cell;
    struct instruction_node * next;
} code_cell_node;

typedef struct data_node {
    DataCell *cell;
    struct data_node * next;
} data_cell_node;

typedef struct entry_extern_node {
	EntryExternCell* cell;
	struct entry_extern_node * next;
} entry_extern_cell_node;

void add_code(CodeCell* cell);
/* adds the code cell to the list of code cells (the code section)*/
void add_data(DataCell *cell);
/* adds the data cell to the data section */
void add_ent_ext(EntryExternCell *cell);
/* adds a label originated in a .entry or .extern guidance sentence into the ent_ext labels section */

code_cell_node* get_code_section();
data_cell_node* get_data_section();
entry_extern_cell_node* get_ent_ext_section();
int is_label_ext(char *label);

int IC;
int DC;
#endif