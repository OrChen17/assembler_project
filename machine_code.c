#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"

int IC = 0;
int DC = 0;

code_cell_node* start;
code_cell_node* end;
data_cell_node* start;
data_cell_node* end;

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

void add_data(DataCell *cell) {
    if (start == NULL) {
        start = malloc(sizeof(data_cell_node));
        start->cell = cell;
        start->next = NULL;
        end = start;
    }
    else {
        end->next = malloc(sizeof(data_cell_node));
        end->next->cell = cell;
        end->next->next = NULL;
        end = end->next;
    }
    DC++;
}

code_cell_node* get_code_section() {
    code_cell_node* p = start;
    return p;
}

data_cell_node* get_data_section() {
    data_cell_node* p = start;
    return p;
}