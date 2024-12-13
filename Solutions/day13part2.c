#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 10
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 140
#endif

int min(int a, int b);

int main() {
    FILE* f = fopen(FILE_NAME, "r");


    int tokens = 0;

    while (!feof(f)) {
        int ax, ay, bx, by;
        long px, py;
        fscanf(f, "Button A: X+%d, Y+%d ", &ax, &ay);
        fscanf(f, "Button B: X+%d, Y+%d ", &bx, &by);
        fscanf(f, "Prize: X=%ld, Y=%ld ", &px, &py);

        long minTokens = __LONG_MAX__;

        if ((ax/3.0)*(ax/3.0) + (ay/3.0)*(ay/3.0) > bx*bx + by*by) {

        }
        else {

        }
    }

    printf("%d\n", tokens);
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}