#include <helper.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_convert_b32() {
    CodeCell *code_cell = malloc(sizeof(CodeCell));
    code_cell->encoding_type = ENCODING_TYPE_A;
    code_cell->data = 0;

    char *b32 = code_cell_to_b32(code_cell);
    printf("%s\n", b32);
    assert(strcmp(b32, "!!") == 0);

    code_cell->data = 1;
    b32 = code_cell_to_b32(code_cell);
    printf("%s\n", b32);
    assert(strcmp(b32, "!%") == 0);
    
    code_cell->data = 16;
    b32 = code_cell_to_b32(code_cell);
    printf("%s\n", b32);
    assert(strcmp(b32, "#!") == 0);

    code_cell->data = -1;
    code_cell->encoding_type = ENCODING_TYPE_R;
    b32 = code_cell_to_b32(code_cell);
    printf("%s\n", b32);
    assert(strcmp(b32, "vu") == 0);
}

int main() {
    test_convert_b32();
    printf("Success!");
    return 1;
}