#include "helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "machine_code.h"
#include "validator.h"
#include "symbol_table.h"
#include "guidance_parser.h"

int parse_guidance(DataGuiding *guidance) {
    int i;
    char* token;
    validate_guidance_input(guidance->guidance_word, guidance->guidance_input);
    //add_symbol
    if (strcmp(guidance->guidance_word, ".data"))
    {
        
        token = strtok(guidance->guidance_input, " \t,");
        while (token != NULL)
        {
            add_data//
        }
        
    }
    else if (strcmp(guidance->guidance_word, ".string"))
    {

    }
    else if (strcmp(guidance->guidance_word, ".struct"))
    {

    }
    // else if entry or extern --> put into files. Here or not here?
}