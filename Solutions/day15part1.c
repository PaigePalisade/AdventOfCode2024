#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 10
#endif

#ifdef TEST2
#define FILE_NAME "test2.txt"
#define SIZE 8
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 50
#endif

char map[SIZE][SIZE];

int move(int r, int c, char direction, char replace);
void printMap();

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // robot row, column
    int rr, rc;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            char symbol;
            fscanf(f, "%c ", &symbol);
            map[r][c] = symbol;
            if (symbol == '@') {
                rr = r;
                rc = c;
            }
        }
    }

    printMap();

    while (!feof(f)) {
        char direction;
        fscanf(f, "%c ", &direction);
        int moved = move(rr, rc, direction, '.');
        if (moved) {
            if (direction == 'v') {
                rr ++;
            }
            if (direction == '^') {
                rr --;
            }
            if (direction == '>') {
                rc ++;
            }
            if (direction == '<') {
                rc --;
            }
        }
    }
    printMap();

    int sum = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (map[r][c] == 'O') {
                sum += r * 100 + c;
            }
        }
    }

    printf("%d\n", sum);
}

int move(int r, int c, char direction, char replace) {
    if (map[r][c] == '#') {
        return 0;
    }
    if (map[r][c] == '.') {
        map[r][c] = replace;
        return 1;
    }
    int ableToMove = 0;
    if (r + 1 < SIZE-1 && direction == 'v') {
        ableToMove = move(r+1, c, direction, map[r][c]);
    }
    if (r - 1 > 0 && direction == '^') {
        ableToMove = move(r-1, c, direction, map[r][c]);
    }
    if (c + 1 < SIZE*2-1 && direction == '>') {
        ableToMove = move(r, c+1, direction, map[r][c]);
    }
    if (c - 1 > 0 && direction == '<') {
        ableToMove = move(r, c-1, direction, map[r][c]);
    }
    if (ableToMove) {
        map[r][c] = replace;
    }
    return ableToMove;
}

void printMap() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            printf("%c", map[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}