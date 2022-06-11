#include <helper.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <file_handler.h>

void test_convert_b32() {
    CodeCell *code_cell = malloc(sizeof(CodeCell));
    code_cell->encoding_type = ENCODING_TYPE_A;
    code_cell->data = 0;

    char *b32 = code_cell_to_b32(code_cell);
    assert(strcmp(b32, "!!") == 0);

    code_cell->data = 1;
    b32 = code_cell_to_b32(code_cell);
    assert(strcmp(b32, "!%") == 0);
    
    code_cell->data = 16;
    b32 = code_cell_to_b32(code_cell);
    assert(strcmp(b32, "#!") == 0);

    code_cell->data = -1;
    code_cell->encoding_type = ENCODING_TYPE_R;
    b32 = code_cell_to_b32(code_cell);
    assert(strcmp(b32, "vu") == 0);
    printf("test_convert_b32 passed\n");
}

void test_is_empty_line() {
    char *line = "";
    assert(is_empty_line(line) == 1);

    line = " ";
    assert(is_empty_line(line) == 1);

    line = " \n";
    assert(is_empty_line(line) == 1);

    line = "asdasd\n";
    assert(is_empty_line(line) == 0);
    printf("Done testing is_empty_line\n");
}

int main() {
    test_convert_b32();
    test_is_empty_line();
    printf("Success!");
    return 1;
}