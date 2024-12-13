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
        int ax, ay, bx, by, px, py;
        fscanf(f, "Button A: X+%d, Y+%d ", &ax, &ay);
        fscanf(f, "Button B: X+%d, Y+%d ", &bx, &by);
        fscanf(f, "Prize: X=%d, Y=%d ", &px, &py);

        int minTokens = __INT_MAX__;

        for (int a = 0; a <= 100; a++) {
            for (int b = 0; b <= 100; b++) {
                if (ax * a + bx * b == px && ay * a + by * b == py) {
                     minTokens = min(minTokens, 3 * a + b);
                }
            }
        }
        if (minTokens != __INT_MAX__) {
            printf("%d\n", minTokens);
            tokens += minTokens;
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