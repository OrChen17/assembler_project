#include <stdio.h>
#include <math.h>


enum EncodingType {
    A = 0,
    E = 1,
    R = 2
};

enum OpCodes {
    mov = 0,
    cmp =  1,
    add =  2,
    sub =  3,
    not =  4,
    clr =  5,
    lea =  6,
    inc =  7,
    dec =  8,
    jmp =  9,
    bne = 10,
    get = 11,
    prn = 12,
    jsr = 13,
    rts = 14,
    hlt = 15
};

enum AddressingMode {
    Immediate = 0,
    Direct = 1,
    DirectParam = 2,
    Register = 3
};

char IndexToBase32(int i) {
    char *b32[] = {
        '!',
        '@',
        '#',
        '$',
        '%',
        '^',
        '&',
        '*',
        '<',
        '>',
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
    };
    return b32[i];
}

int BinaryToInt(int* binary) {
    int total = 0;
    int size = sizeof(binary) / sizeof(int);
    for (int i=0; i < size; i++) {
        if (binary[i] == 1) {
            total += pow(2, i);
        };
    }

    return total;
}

char * BinaryToBase32(int* binary) {
    int number = BinaryToInt(binary);
    int leftover = number % 32;
    int remainder = (number - leftover) / 32;

    if (remainder != 0) {
        char* res[] = {IndexToBase32(remainder), IndexToBase32(leftover), '\0'};
        return res;
    }
    else {
        char* res[] = {IndexToBase32(leftover), '\0'};
        return res;
    }
}

void main() {
    int bin[] = {0, 0, 0};
    char *res = BinaryToBase32(bin);
    printf("{0,0,0} should be (!) == %s", res);
}