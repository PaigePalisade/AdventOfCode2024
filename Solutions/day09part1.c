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

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char str[30000];

    fscanf(f, "%s ", &str);

    // read input
    int mem[200000];
    int memSize = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            int run = str[i] - '0';
            for (int j = 0; j < run; j++) {
                mem[memSize] = i/2;
                memSize ++;
            }
        }
        else {
            int run = str[i] - '0';
            for (int j = 0; j < run; j++) {
                mem[memSize] = -1;
                memSize ++;
            }
        }
    }
    
    // move blocks to free space
    for (int i = 0; i < memSize; i++) {
        if (mem[i] == -1) {
            mem[i] = mem[memSize-1];
            memSize --;
            while (mem[memSize-1] == -1) {
                memSize --;
            }
        }
    }

    // calculate sum
    long sum = 0;
    for (int i = 0; i < memSize; i++) {
        sum += mem[i] * i;
    }

    printf("%ld\n", sum);
}