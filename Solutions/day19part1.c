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

// recursively check substrings of the pattern

char towels[500][20];
int numTowels = 0;

int checkTowels(char* pattern);

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
    int sum = 0;
    while (!feof(f)) {
        char pattern[100];
        fscanf(f, "%s ", &pattern);
        if (checkTowels(pattern)) {
            printf("Pattern: %s\n", pattern);
            sum ++;
        }
    }
    printf("%d\n", sum);
}

int checkTowels(char* pattern) {
    int patternLen = strlen(pattern);
    for (int i = 0; i < numTowels; i++) {
        int towelLen = strlen(towels[i]);
        if (towelLen == patternLen && strcmp(pattern, towels[i]) == 0) {
            return 1;
        }
        if (towelLen < patternLen && strncmp(pattern, towels[i], towelLen) == 0) {
            if (checkTowels(pattern + towelLen)) {
                return 1;
            }
        }
    }
    return 0;
}