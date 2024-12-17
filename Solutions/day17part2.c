#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#endif

int isQuine(long a, int numToCheck);
long findQuine(long a, int n);

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

    // My input is structured in the following pattern:
    // (specifics are not shown due to rules on sharing input files)
    // while (A != 0) {
        // ..B and C are modified based on A and some constants..
        // A /= 8
        // print B % 8
    // }
    // The program will only output log(A, 8) + 1 outputs
    // I check for each value of A (1-7) that it equals the last int of the program
    // then I multiply that value of A by 8 and add values 1-7
    // and test if they produce the last 2 ints of the program
    // etc until I have the program
    // If your input is not structured like mine, it won't work,
    // but I assume they all are

    a = findQuine(0, 1);

    printf("%ld\n", a);
    assert(isQuine(a, programSize));
}

// finds a value for A that is a quine, returns A if found, -1 otherwise
long findQuine(long a, int n) {
    if (n > programSize) {
        return a;
    }
    for (int i = 0; i < 8; i++) {
        long result;
        if (isQuine(a * 8 + i, n)) {
            result = findQuine(a * 8 + i, n + 1);
            if (result != -1) {
                return result;
            }
        }
    }
    return -1;
}

int isQuine(long a, int numToCheck) {
    long b = 0;
    long c = 0;

    int numOutput = 0;

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
            int out = combr % 8;
            if (program[programSize - numToCheck + numOutput] != out) {
                return 0;
            }
            numOutput ++;
            if (numOutput == numToCheck) {
                return 1;
            }
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
    return 0;
}