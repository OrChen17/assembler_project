/* parses each line from its bare text to a "InstructionComponents" / GuidingComponents struct, 
which has the parsed sections of the line - label, operands, opcode etc. passes the instruction to the instruction parser */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <line_parser.h>
#include <instruction_parser.h>
#include <ctype.h>
#include <validator.h>
#include <helper.h>
#include <guidance_parser.h>

InstructionComponents* parse_data_instruction(char *instruction_to_parse) {
    int i;
    char* operand_1;
    char* operand_2;
    InstructionComponents *instruction = malloc(150);
    char *token;
    strcpy(instruction->label, "");
    token = strtok(instruction_to_parse, " \t\n");
    if (token == NULL) {
        strcpy(instruction->opcode, trim_whitespace(instruction_to_parse)); /* ##CR: if token is NULL already here, what's the point of this command?*/
        return instruction;
    }
    if (token[strlen(token) - 1] == ':') { /* ##CR: what if we have spaces between the label and the colon? */
        char label[31];
        if (strlen(token) > 31)
        {
            printf("label too long: %s\n", token);
            has_found_error = 1;
        }
        else
        {
            strncpy(label, token, strlen(token) - 1);
            label[strlen(token) - 1] = '\0';
            strcpy(instruction->label, trim_whitespace(label));
            validate_label(instruction->label);
            check_duplicate_label(instruction->label);
        }
        token = strtok(NULL, " \t\n");
    }
    if (token == NULL)
        {
            printf("Error: Empty label\n");
            has_found_error = 1;
        }
    else
    {
            strcpy(instruction->opcode, trim_whitespace(token));
            token = strtok(NULL, "");
            if (token == NULL) {
                return instruction;
            }
            operand_1 = malloc(sizeof(char) * strlen(token) + 1);
            operand_2 = malloc(sizeof(char) * strlen(token) + 1);
            for (i = 0; i < strlen(token); i++) {
                if (token[i] == ',') {
                    strncpy(operand_1, token, i);
                    operand_1[i] = '\0';
                    if (strlen(operand_1) == 0) {
                        operand_1 = NULL;
                        printf("Found empty operand 1 with , \n");
                        /* ##CR: When getting here (with proper example) --> segfault */
                        has_found_error = 1;
                    }
                    strcpy(instruction->operand_1, trim_whitespace(operand_1));

                    strncpy(operand_2, token + i + 1, strlen(token) - i); /* add null terminator */
                    if (strlen(operand_2) == 0) {
                        printf("Invalid empty operand\n");
                        has_found_error = 1;
                    }

                    strcpy(instruction->operand_2, trim_whitespace(operand_2));
                    return instruction;
                }
            }
            /* ##CR: no "," */
        if (strlen(trim_whitespace(token)) != 0) {
            strcpy(instruction->operand_2, trim_whitespace(token));
        }
    }
    return instruction;
}

GuidingComponents* parse_guiding_line_to_struct(char* guidance_to_parse) {
    char *token;
    GuidingComponents* guidance = malloc(250);
    strcpy(guidance->label, "");
    token = strtok(guidance_to_parse, " \t\n");
    if (token[strlen(token) - 1] == ':') { /* ##CR: what if we have spaces between the label and the colon? */
        char label[31];
        if (strlen(token) > 31)
        {
            printf("label too long: %s\n", token);
            has_found_error = 1;
        }
        else
        {
            strncpy(label, token, strlen(token) - 1);
            label[strlen(token) - 1] = '\0';
            strcpy(guidance->label, trim_whitespace(label));
            validate_label(guidance->label);
            check_duplicate_label(guidance->label);
        }
        token = strtok(NULL, " \t\n");
    }
    strcpy(guidance->guidance_word, trim_whitespace(token));
    validate_guidance_word(guidance->guidance_word);
    if (!(strcmp(guidance->guidance_word, ".entry") || !strcmp(guidance->guidance_word, ".extern"))
        && strcmp(guidance->label, ""))
        {
            strcpy(guidance->label, "");
            printf("Warning: .entry and .extern guidance words should not have labels. Ignoring label\n");
        }
    token = strtok(NULL, "\n");
    if (token != NULL)
    {
        strcpy(guidance->guidance_input, token);
    }
    else
    {
        printf("Error: a guidance line must have an input\n");
        has_found_error = 1;
    }
    return guidance;
}

int parse_instruction_line(char *instruction_to_parse) {
    InstructionComponents *instruction = parse_data_instruction(instruction_to_parse);
    return parse_instruction(instruction);
}

int parse_guiding_line(char *guidance_to_parse) {
    GuidingComponents *guidance = parse_guiding_line_to_struct(guidance_to_parse);
    return parse_guidance(guidance);
}