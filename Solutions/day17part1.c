#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#endif

#ifdef TEST2
#define FILE_NAME "test2.txt"
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#endif

void evaluate(long a, long b, long c);

int program[20];
int programSize = 0;

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    long a, b, c;

    fscanf(f, "Register A: %ld ", &a);
    fscanf(f, "Register B: %ld ", &b);
    fscanf(f, "Register C: %ld ", &c);

    fscanf(f, "Program: ");
    while (!feof(f)) {
        fscanf(f, "%d ", &program[programSize]);
        programSize ++;
        if (!feof(f)) {
            fscanf(f, ",");
        }
    }
    evaluate(a, b, c);
    printf("\n");

}

void evaluate(long a, long b, long c) {
    for (int ip = 0; ip < programSize; ip+=2) {
        assert(ip >= 0);
        int opc = program[ip];
        int opr = program[ip+1];
        long combr = opr;
        if (opr == 4) {
            combr = a;
        }
        if (opr == 5) {
            combr = b;
        }
        if (opr == 6) {
            combr = c;
        }
        // adv
        if (opc == 0) {
            a /= 1 << combr;
        }
        // bxl
        if (opc == 1) {
            b ^= opr;
        }
        // bst
        if (opc == 2) {
            b = combr % 8;
        }
        // jnz
        if (opc == 3) {
            if (a != 0) {
                ip = opr - 2;
            }
        }
        // bxc
        if (opc == 4) {
            b ^= c;
        }
        // out
        if (opc == 5) {
            printf("%ld,", combr % 8);
        }
        // bdv
        if (opc == 6) {
            b = a / (1 << combr);
        }
        // cdv
        if (opc == 7) {
            c = a / (1 << combr);
        }
    }
}
