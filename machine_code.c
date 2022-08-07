/*inputs data and code cells to theie respective section, implemented with a linked list */
#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"

int IC = 0;
int DC = 0;

code_cell_node* start;
code_cell_node* end;
data_cell_node* data_start;
data_cell_node* data_end;

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
    if (data_start == NULL) {
        data_start = malloc(sizeof(data_cell_node));
        data_start->cell = cell;
        data_start->next = NULL;
        data_end = data_start;
    }
    else {
        data_end->next = malloc(sizeof(data_cell_node));
        data_end->next->cell = cell;
        data_end->next->next = NULL;
        data_end = data_end->next;
    }
    DC++;
}

code_cell_node* get_code_section() {
    code_cell_node* p = start;
    return p;
}

data_cell_node* get_data_section() {
    data_cell_node* p = data_start;
    return p;
}