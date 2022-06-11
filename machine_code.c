#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"

int IC = 0;
int DC = 0;

node_t* code_section;

void add_code(CodeCell *cell) {
    if (code_section == NULL) {
        code_section = malloc(sizeof(node_t));
        code_section->cell = cell;
        code_section->next = NULL;
    }
    else {
        node_t *cur = code_section;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(node_t));
        cur->next->cell = cell;
        cur->next->next = NULL;
    }
    IC++;
}

node_t* get_code_section() {
    return code_section;
}

// DataCell - 10 bits data,