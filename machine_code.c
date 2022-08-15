/*inputs data and code cells to theie respective section, implemented with a linked list */
#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"
#include <stdio.h>

int IC = 0;
int DC = 0;

code_cell_node* start;
code_cell_node* end;
data_cell_node* data_start;
data_cell_node* data_end;
entry_extern_cell_node* ent_ext_start;
entry_extern_cell_node* ent_ext_end;

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
    /*printf("IC: %d\n", IC);
    printf("DC: %d\n", DC);*/
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
    /*printf("IC: %d\n", IC);
    printf("DC: %d\n", DC);*/
}

void add_ent_ext(EntryExternCell *cell) {
    if (ent_ext_start == NULL) {
        ent_ext_start = malloc(sizeof(entry_extern_cell_node));
        ent_ext_start->cell = cell;
        ent_ext_start->next = NULL;
        ent_ext_end = ent_ext_start;
    }
    else {
        ent_ext_end->next = malloc(sizeof(entry_extern_cell_node));
        ent_ext_end->next->cell = cell;
        ent_ext_end->next->next = NULL;
        ent_ext_end = ent_ext_end->next;
    }
}

code_cell_node* get_code_section() {
    code_cell_node* p = start;
    return p;
}

data_cell_node* get_data_section() {
    data_cell_node* p = data_start;
    return p;
}

entry_extern_cell_node* get_ent_ext_section() {
    entry_extern_cell_node* p = ent_ext_start;
    return p;
}