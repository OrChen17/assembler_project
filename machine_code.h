#ifndef MACHINE_CODE
#define MACHINE_CODE
#include <helper.h>

typedef struct node {
    CodeCell* cell;
    struct node * next;
} code_cell_node;

typedef struct data_node {
    DataCell *cell;
    struct data_node * next;
} data_cell_node;

void add_code(CodeCell* cell);
/* adds the code cell to the list of code cells (the code section)*/
void add_data(DataCell *cell);
/* adds the data cell to the data section */
code_cell_node* get_code_section();

int IC;
int DC;
#endif