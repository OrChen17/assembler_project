#include "unfold_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

macro_cell_node* macro_start;
macro_cell_node* new_cell;

void add_macro_to_macros_table(MacroCell * cell)
{
    if (macro_start == NULL)
    {
        macro_start = malloc(sizeof(macro_cell_node));
        strcpy(macro_start->name, cell->name);
        strcpy(macro_start->content, cell->content);
        macro_start->next = NULL;
    }
    else
    {
        new_cell = malloc(sizeof(macro_cell_node));
        strcpy(new_cell->name, cell->name);
        strcpy(new_cell->content, cell->content);
        new_cell->next = macro_start;
        macro_start = new_cell;
    }
}

int not_in_macros_table(char* token)
{
    macro_cell_node* p;
    if (macro_start == NULL)
    {
        return 1;
    }
    else
    {
        p = macro_start;
        while (p->next != NULL)
        {
            if (strcmp(p->name, token) == 0)
            {
                return 0;
            }
            p = p->next;
        }
    }
    if (strcmp(p->name, token) == 0)
        {
            return 0;
        }
    else
    {
        return 1;
    }
}

char* unfold_single_macro(char * token)
{
    macro_cell_node* p;
    char *content;

    p = macro_start;
    if (p->next == NULL)
    {
        content = p->content;
        return content;
    }
    while (p->next != NULL)
    {
        if (strcmp(p->name, token) == 0)
        {
            content = p->content;
            break;
        }
        p = p->next;
    }
    if (strcmp(p->name, token) == 0)
        {
            content = p->content;
        }
    return content; 
}

void free_macros_table(macro_cell_node* macro_start)
{
    macro_cell_node* to_free;
    to_free = macro_start->next;
    free(macro_start);
    if (to_free != NULL)
    {
        while (to_free->next != NULL)
        {
            to_free = to_free->next;
            free(to_free);
        }
    }
}

char* unfold_macros(FILE *input_file)
{
    FILE* pre_assembled_file;
    char line[83];
    char tokenized_line[83];
    char *token;
    char *name;
    char *content;
    MacroCell *macro_cell = malloc(sizeof(MacroCell));
    
    pre_assembled_file = fopen(PRE_ASSEMBLED_FILE_NAME, "w+"); /* I'm assuming here that we can use the same file name for all the files given as inputs */
    while (fgets(line, 83, input_file)) {
        /*printf("line is: %s", line);*/
        strcpy(tokenized_line, line);
        token = strtok(tokenized_line, " \t\n");
        /*printf("token is: %s\n", token);*/
        if (token == NULL)
        {
            fprintf(pre_assembled_file, "%s", line);
            continue;
        }
        if (strcmp(token, "macro") == 0)
        {
            name = strtok(NULL, " \t\n");
            content = malloc(500);
            strcpy(content, "");
            fgets(line, 83, input_file);
            while (strcmp(line, "endmacro\n") != 0)
            {
                strcat(content, line + 1);
                fgets(line, 83, input_file);
            }
            strcpy(macro_cell->name, name);
            strcpy(macro_cell->content, content);
            free(content);
            add_macro_to_macros_table(macro_cell);
        }
        else
        {
            if (not_in_macros_table(token))
            {
                fprintf(pre_assembled_file, "%s", line);
            }
            else
            {
                content = unfold_single_macro(token);
                fprintf(pre_assembled_file, "%s", content);
            }
        }
    }
    if (macro_start != NULL)
    {
        free_macros_table(macro_start);
    }
    fclose(pre_assembled_file);
    free(macro_cell);
    return PRE_ASSEMBLED_FILE_NAME;
}