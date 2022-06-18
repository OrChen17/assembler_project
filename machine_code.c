#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"

int IC = 0;
int DC = 0;

code_cell_node* start;
code_cell_node* end;

void add_code(CodeCell *cell) {
    if (start == NULL) {
        start = malloc(sizeof(code_cell_node));
        start->cell = cell;
        start->next = NULL;
        end = start;
    }
    else {
        end->next = malloc(sizeof(code_cell_node));
        end->next->cell = cell;
        end->next->next = NULL;
        end = end->next;
    }
    IC++;
}

code_cell_node* get_code_section() {
    code_cell_node* p = start;
    return p;
}

// DataCell - 10 bits data,