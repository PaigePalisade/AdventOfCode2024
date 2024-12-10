#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 8
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 45
#endif

void search(int r, int c, int map[SIZE][SIZE], int score[SIZE][SIZE], int mask[SIZE][SIZE]) {
    int num = map[r][c];

    if (num == 0) {
        if (!mask[r][c]) {
            score[r][c] ++;
            mask[r][c] = 1;
        }
        return;
    }

    if (r + 1 < SIZE && map[r+1][c] == num - 1) {
        search(r+1,c, map, score, mask);
    }
    if (r - 1 >= 0 && map[r-1][c] == num - 1) {
        search(r-1,c, map, score, mask);
    }
    if (c + 1 < SIZE && map[r][c+1] == num - 1) {
        search(r,c+1, map, score, mask);
    }
    if (c - 1 >= 0 && map[r][c-1] == num - 1) {
        search(r,c-1, map, score, mask);
    }
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    int map[SIZE][SIZE];

    int score[SIZE][SIZE] = {0};

    
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            char chr = ' ';
            fscanf(f, "%c ", &chr);
            map[r][c] = chr - '0';
        }
    }

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (map[r][c] == 9) {
                int mask[SIZE][SIZE] = {0};
                search(r, c, map, score, mask);
            }
        }
    }

    int sum = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (score[r][c] != 0) {
                sum += score[r][c];
            }
        }
    }
    printf("%d\n", sum);
}