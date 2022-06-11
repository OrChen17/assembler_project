#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"

int IC = 0;
int DC = 0;

code_cell_node* code_section;

void add_code(CodeCell *cell) {
    if (code_section == NULL) {
        code_section = malloc(sizeof(code_cell_node));
        code_section->cell = cell;
        code_section->next = NULL;
    }
    else {
        code_cell_node *cur = code_section;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(code_cell_node));
        cur->next->cell = cell;
        cur->next->next = NULL;
    }
    IC++;
}

code_cell_node* get_code_section() {
    return code_section;
}

// DataCell - 10 bits data,