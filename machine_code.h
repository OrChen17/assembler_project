#ifndef MACHINE_CODE
#define MACHINE_CODE
#include <helper.h>

typedef struct node {
    CodeCell* cell;
    struct node * next;
} node_t;

void add_code(CodeCell* cell);
node_t* get_code_section();

int IC;
int DC;
#endif // !MACHINE_CODE