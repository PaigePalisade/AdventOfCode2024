#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 140

char map[SIZE][SIZE+1];

int checkHorizontal(int i, int j, const char word[]) {
    if (j <= SIZE - 4) {
        return strncmp(&map[i][j], word, 4) == 0;
    }
    return 0;
}

int checkVertical(int i, int j, const char word[]) {
    if (i <= SIZE - 4) {
        int match = 1;
        for (int k = 0; k < 4; k++) {
            if (map[i+k][j] != word[k]) {
                match = 0;
            }
        }
        return match;
    }
    return 0;
}

int checkDiagonalLeft(int i, int j, const char word[]) {
    if (i <= SIZE - 4 && j <= SIZE-4) {
        int match = 1;
        for (int k = 0; k < 4; k++) {
            if (map[i+k][j+k] != word[k]) {
                match = 0;
            }
        }
        return match;
    }
    return 0;
}

int checkDiagonalRight(int i, int j, const char word[]) {
    if (i <= SIZE - 4 && j >= 4-1) {
        int match = 1;
        for (int k = 0; k < 4; k++) {
            if (map[i+k][j-k] != word[k]) {
                match = 0;
            }
        }
        return match;
    }
    return 0;
}

int main() {
    FILE* f = fopen("input.txt", "r");

    for (int i = 0; i < SIZE; i++) {
        fscanf(f, "%s ", &map[i]);
    }

    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            count += checkHorizontal(i, j, "XMAS");
            count += checkHorizontal(i, j, "SAMX");

            count += checkVertical(i, j, "XMAS");
            count += checkVertical(i, j, "SAMX");

            count += checkDiagonalLeft(i, j, "XMAS");
            count += checkDiagonalLeft(i, j, "SAMX");

            count += checkDiagonalRight(i, j, "XMAS");
            count += checkDiagonalRight(i, j, "SAMX");
        }
    }

    printf("%d\n", count);
}