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

// used memoization to reduce on calls to checkTowels

char towels[500][20];
int numTowels = 0;

long checkTowels(char* pattern, int patternIndex, long table[100]);

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    char c = ',';
    while (c == ',') {
        int len = 0;
        c = '.';
        while (c != '\n' && c != ',') {
            fscanf(f, "%c", &c);
            towels[numTowels][len] = c;
            len ++;
        }
        fscanf(f, " ");
        towels[numTowels][len-1] = '\0';
        numTowels ++;
    }
    long sum = 0;
    while (!feof(f)) {
        char pattern[100];
        long table[100];
        for (int i = 0; i < 100; i++) {
            table[i] = -1;
        }
        fscanf(f, "%s ", &pattern);
        long combinations = checkTowels(pattern, 0, table);
        if (combinations != 0) {
            printf("%s: %ld\n", pattern, combinations);
            sum += combinations;
        }
    }
    printf("%ld\n", sum);
}

long checkTowels(char* pattern, int patternIndex, long table[100]) {
    if (table[patternIndex] != -1) {
        return table[patternIndex];
    }
    char* subPattern = pattern + patternIndex;
    int subLen = strlen(subPattern);
    long result = 0;
    for (int i = 0; i < numTowels; i++) {
        int towelLen = strlen(towels[i]);
        if (towelLen == subLen && strcmp(subPattern, towels[i]) == 0) {
            result ++;
        }
        if (towelLen < subLen && strncmp(subPattern, towels[i], towelLen) == 0) {
            result += checkTowels(pattern, patternIndex+towelLen, table);
        }
    }
    table[patternIndex] = result;
    return result;
}