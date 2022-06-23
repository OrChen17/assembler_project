#include "unfold_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

macro_cell_node* start;

void add_macro_to_macros_table(MacroCell * cell)
{
    macro_cell_node *new_cell;
    if (start == NULL)
    {
        start = malloc(sizeof(macro_cell_node));
        start->cell = cell;
        start->next = NULL;
    }
    else
    {
        new_cell = malloc(sizeof(macro_cell_node));
        new_cell->cell = cell;
        new_cell->next = start;
        start = new_cell;
    }
}

int not_in_macros_table(char* token)
{
    macro_cell_node* p = malloc(sizeof(macro_cell_node));
    p = start;
    while (p->next != NULL)
    {
        if (strcmp(p->cell->name, token) == 0)
        {
            free(p);
            return 0;
        }
    }
    free(p);
    return 1;
}

/*char* unfold_single_macro(char * token)
{
    macro_cell_node* p = malloc(sizeof(macro_cell_node));
    char *content;
    p = start;
    while (p->next != NULL)
    {
        if (strcmp(p->cell->name, token) == 0)
        {
            content = p->cell->content;
            break;
        }
    }
    free(p);
    return content; 
}*/

void free_macros_table(macro_cell_node* start)
{
    macro_cell_node* to_free;
    to_free = start->next;
    free(start);
    while (to_free != NULL)
    {
        to_free = to_free->next;
        free(to_free);
    }
}

FILE* unfold_macros(FILE *input_file)
{
    FILE* pre_assembled_file;
    char line[83];
    char tokenized_line[83];
    char *token;
    char *name;
    char *content;
    MacroCell *macro_cell = malloc(sizeof(MacroCell));
    
    pre_assembled_file = fopen("pre_assembled_file", "w+"); //I'm assuming here that we can use the same file name for all the files given as inputs
    while (fgets(line, 83, input_file)) {
        strcpy(tokenized_line, line);
        token = strtok(tokenized_line, " \t");
        if (strcmp(token, "macro") == 0)
        {
            name = strtok(NULL, " \t");
            printf("%s\n", name);
            /* validate_mcaros_name */
            content = malloc(500);
            strcpy(content, "");
            fgets(line, 83, input_file);
            while (strcmp(line, "endmacro\n") != 0)
            {
                strcat(content, line);
                fgets(line, 83, input_file);
            }
            printf("%s\n", content);
            strcpy(macro_cell->name, name);
            strcpy(macro_cell->content, content);
            free(content);
            add_macro_to_macros_table(macro_cell);
        }
        else
        {
            if (not_in_macros_table(token))
            {
                fputs(line, pre_assembled_file);
            }
            /*else
            {
                content = unfold_single_macro(token);
                fputs(content, pre_assembled_file);
                fputs("\n", pre_assembled_file);
            }*/
        }
    }
    free_macros_table(start);
    fclose(pre_assembled_file);
    free(macro_cell);
    return pre_assembled_file;
}