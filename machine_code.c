/*inputs data and code cells to their respective section, implemented with a linked list */
#include <helper.h>
#include <stdlib.h>
#include "machine_code.h"
#include <stdio.h>
#include <string.h>

/*counters for instructions and guidances*/
int IC = 0;
int DC = 0;

/*linked lists parameters*/
code_cell_node* start;
code_cell_node* end;
data_cell_node* data_start;
data_cell_node* data_end;
entry_extern_cell_node* ent_ext_start;
entry_extern_cell_node* ent_ext_end;

void add_code(CodeCell *cell) {
    /* adds the code cell to the list of code cells (the code section)*/
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
    /* adds the data cell to the data section */
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

void add_ent_ext(EntryExternCell *cell) {
    /* adds a label originated in a .entry or .extern guidance sentence into the ent_ext labels section */
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

int is_label_ext(char *label) {
    entry_extern_cell_node *cur = ent_ext_start;
    while (cur != NULL) {
        if (strcmp(cur->cell->label, label) == 0) {
            if (cur->cell->label_type == LABEL_TYPE_EXTERN) {
                return 1;
            }
            else {
                return 0;
            }
        }
        cur = cur->next;
    }
    return 0;
}

code_cell_node* get_code_section() {
    /*returns the head of the code list*/
    code_cell_node* p = start;
    return p;
}

data_cell_node* get_data_section() {
    /*returns the head of the data list*/
    data_cell_node* p = data_start;
    return p;
}

entry_extern_cell_node* get_ent_ext_section() {
    /*returns the head of the EntExt list*/
    entry_extern_cell_node* p = ent_ext_start;
    return p;
}

void free_code_list()
/*Frees the code cell nodes in the code cells list*/
{
    code_cell_node* code_cell_start;
    code_cell_node* to_free;
    
    code_cell_start = get_code_section();
    if (code_cell_start !=NULL)
    {
        to_free = code_cell_start->next;
        free(code_cell_start);
        if (to_free != NULL)
        {
            while (to_free->next != NULL)
            {
                free(to_free);
                to_free = to_free->next;
            }
        }
    }
    start = NULL;
    end = NULL;
    IC = 0;
}

void free_data_list()
/*Frees the data cell nodes in the data cells list*/
{
    data_cell_node* data_cell_start;
    data_cell_node* to_free;
    
    data_cell_start = get_data_section();
    if (data_cell_start !=NULL)
    {
        to_free = data_cell_start->next;
        free(data_cell_start);
        if (to_free != NULL)
        {
            while (to_free->next != NULL)
            {
                free(to_free);
                to_free = to_free->next;
            }
        }
    }
    data_start = NULL;
    data_end = NULL;
    DC = 0;
}

void free_ent_ext_list()
/*Frees the EntExt cell nodes in the EntExt cells list*/
{
    entry_extern_cell_node* entry_extern_cell_start;
    entry_extern_cell_node* to_free;
    
    entry_extern_cell_start = get_ent_ext_section();
    if (entry_extern_cell_start !=NULL)
    {
        to_free = entry_extern_cell_start->next;
        free(entry_extern_cell_start);
        if (to_free != NULL)
        {
            while (to_free->next != NULL)
            {
                free(to_free);
                to_free = to_free->next;
            }
        }
    }
    ent_ext_start = NULL;
    ent_ext_end = NULL;
}