/*Contains functions which allow macros unfolding*/

#include "unfold_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

macro_cell_node* macro_start;

void add_macro_to_macros_table(MacroCell * cell)
/*Adds a detected macro into the linked list*/
{
    macro_cell_node* new_cell;
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
/*Checks if a certain object is a macro*/
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
/*When detecting a macro's name in the original input file, the code comes here in order to look for the
macro's content and write them into the right place in the new file*/
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

void free_macros_table()
{
    macro_cell_node* to_free;
    if (macro_start == NULL) {
        return;
    }
    to_free = macro_start->next;
    free(macro_start);
    if (to_free != NULL)
    {
        while (to_free->next != NULL)
        {
            free(to_free);
            to_free = to_free->next;
        }
    }
    macro_start = NULL;
}

void unfold_macros(char *full_filename_after_macros, FILE *input_file)
/*Goes through the original input file and copies the rows as they are into a new file, unless
the line read starts with the word macro, or contains a macro's name. In the first case it adds the macro's name and contents
into a linked list; in the second case it goes to the list and brings the content, replacing the macro's name with its contents.
The new file that's created is identical to the original file, only with macros unfolded
We assume that macros have no errors in them, as requeted in the excercise*/
{
    FILE* pre_assembled_file;
    char line[83];
    char tokenized_line[83];
    char *token;
    char *name;
    char *content;
    MacroCell *macro_cell = malloc(sizeof(MacroCell));
    
    pre_assembled_file = fopen(full_filename_after_macros, "w");
    while (fgets(line, 83, input_file)) {
        strcpy(tokenized_line, line);
        token = strtok(tokenized_line, " \t\n");
        if (token == NULL)
        {
            fprintf(pre_assembled_file, "%s", line);
            continue;
        }
        if (strcmp(token, "macro") == 0)
        {
            name = strtok(NULL, " \t\n");
            content = malloc(sizeof(char) * 500);
            strcpy(content, "");
            fgets(line, 83, input_file);
            while (strcmp(trim_whitespace(line), "endmacro") != 0)
            {
                strcat(content, trim_whitespace(line));
                content[strlen(content)] = '\n';
                content[strlen(content)] = '\0';
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
    fclose(pre_assembled_file);
}