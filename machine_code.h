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
void add_data(DataCell *cell);
code_cell_node* get_code_section();

int IC;
int DC;
#endif