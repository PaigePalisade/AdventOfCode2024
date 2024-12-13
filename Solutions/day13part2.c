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

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long tokens = 0;

    while (!feof(f)) {
        long ax, ay, bx, by, px, py;
        fscanf(f, "Button A: X+%ld, Y+%ld ", &ax, &ay);
        fscanf(f, "Button B: X+%ld, Y+%ld ", &bx, &by);
        fscanf(f, "Prize: X=%ld, Y=%ld ", &px, &py);

        px += 10000000000000;
        py += 10000000000000;

        long numeratorX = px*by - py*bx;
        long denomiatorX = ax*by - ay*bx;
        
        long numeratorY = px*ay - py*ax;
        long denomiatorY = ay*bx - ax*by;

        if (numeratorX % denomiatorX == 0 && numeratorY % denomiatorY == 0) {
            long a = numeratorX / denomiatorX;
            long b = numeratorY / denomiatorY;
            tokens += 3*a + b;
            printf("%ld\n", 3*a + b);
        }
    }

    printf("%ld\n", tokens);
}