#ifndef MACHINE_CODE
#define MACHINE_CODE
#include <helper.h>

typedef struct node {
    CodeCell* cell;
    struct node * next;
} code_cell_node;

void add_code(CodeCell* cell);
code_cell_node* get_code_section();

int IC;
int DC;
#endif // !MACHINE_CODE