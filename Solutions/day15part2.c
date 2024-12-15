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

typedef struct {
    int r;
    int c;
    char chr;
} Position;

char map[SIZE][SIZE*2];

void printMap();
int getToMove(int r, int c, char direction);
Position toMove[SIZE * SIZE * 2];
int numToMove = 0;
int includesPosition(int r, int c);

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // robot row, column
    int rr, rc;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            char symbol;
            fscanf(f, "%c ", &symbol);
            if (symbol == '@') {
                rr = r;
                rc = c*2;
                map[r][c*2] = '@';
                map[r][c*2+1] = '.';
            }
            else if (symbol == 'O') {
                map[r][c*2] = '[';
                map[r][c*2+1] = ']';
            }
            else {
                map[r][c*2] = symbol;
                map[r][c*2+1] = symbol;
            }
        }
    }

    printMap();

    while (!feof(f)) {
        char direction;
        fscanf(f, "%c ", &direction);
        numToMove = 0;
        int blocked = getToMove(rr, rc, direction);
        // if there are no blocks, move all of the tiles in the toMove list
        if (!blocked) {
            if (direction == 'v') {
                rr++;
            }
            if (direction == '^') {
                rr--;
            }
            if (direction == '>') {
                rc++;
            }
            if (direction == '<') {
                rc--;
            }
            for (int i = 0; i < numToMove; i++) {
                map[toMove[i].r][toMove[i].c] = '.';
                if (direction == 'v') {
                    map[toMove[i].r+1][toMove[i].c] = toMove[i].chr;
                }
                if (direction == '^') {
                    map[toMove[i].r-1][toMove[i].c] = toMove[i].chr;
                }
                if (direction == '>') {
                    map[toMove[i].r][toMove[i].c+1] = toMove[i].chr;
                }
                if (direction == '<') {
                    map[toMove[i].r][toMove[i].c-1] = toMove[i].chr;
                }
            }
        }
    }
    printMap();

    int sum = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE*2; c++) {
            if (map[r][c] == '[') {
                sum += r * 100 + c;
            }
        }
    }

    printf("%d\n", sum);
}

// get's a list of tiles to move (including the robot)
// returns 1 if the robot is blocked along the way
// returns a 0 if it is possible to move
int getToMove(int r, int c, char direction) {
    if (map[r][c] == '.') {
        return 0;
    }
    if (map[r][c] == '#') {
        return 1;
    }
    if (map[r][c] == ']' && (direction == '^' || direction == 'v')) {
        c --;
    }
    int result = 1;
    if (r + 1 < SIZE-1 && direction == 'v') {
        if (map[r][c] == '[') {
            result = getToMove(r+1, c, direction) || getToMove(r+1, c+1, direction);
        }
        else {
            result = getToMove(r+1, c, direction);
        }
    }
    if (r - 1 > 0 && direction == '^') {
        if (map[r][c] == '[') {
            result = getToMove(r-1, c, direction) || getToMove(r-1, c+1, direction);
        }
        else {
            result = getToMove(r-1, c, direction);
        }
    }
    if (c + 1 < SIZE*2-1 && direction == '>') {
        result = getToMove(r, c+1, direction);
    }
    if (c - 1 > 0 && direction == '<') {
        result = getToMove(r, c-1, direction);
    }

    if (!includesPosition(r, c)) {
        toMove[numToMove] = (Position){r, c, map[r][c]};
        numToMove ++;
    }
    if (map[r][c] == '[' && (direction == '^' || direction == 'v')) {
        if (!includesPosition(r, c+1)) {
            toMove[numToMove] = (Position){r, c+1, ']'};
            numToMove ++;
        }
    }

    // assert(iteration != 2275);
    return result;
}

void printMap() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE*2; c++) {
            printf("%c", map[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

// I was getting duplicates in toMove list, so I check for them
int includesPosition(int r, int c) {
    for (int i = 0; i < numToMove; i++) {
        if (r == toMove[i].r && c == toMove[i].c) {
            return 1;
        }
    }
    return 0;
}