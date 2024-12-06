#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 10
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 130
#endif

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char map[SIZE][SIZE];

    int guardRow;
    int guardCol;

    int direction = NORTH;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            fscanf(f, "%c ", &map[r][c]);
            if (map[r][c] == '^') {
                guardRow = r;
                guardCol = c;
            }
        }
    }

    int count = 0;

    while (guardRow >= 0 && guardRow < SIZE && guardCol >= 0 && guardCol < SIZE) {
        if (map[guardRow][guardCol] != 'X') {
            map[guardRow][guardCol] = 'X';
            count ++;
        }
        if (direction == NORTH) {
            guardRow --;
            if (guardRow-1 >= 0 && map[guardRow-1][guardCol] == '#') {
                direction ++;
                direction %= 4;
            }
        }
        else if (direction == EAST) {
            guardCol ++;
            if (guardCol+1 < SIZE && map[guardRow][guardCol+1] == '#') {
                direction ++;
                direction %= 4;
            }
        }
        else if (direction == SOUTH) {
            guardRow ++;
            if (guardRow+1 < SIZE && map[guardRow+1][guardCol] == '#') {
                direction ++;
                direction %= 4;
            }
        }
        else if (direction == WEST) {
            guardCol --;
            if (guardCol-1 >= 0 && map[guardRow][guardCol-1] == '#') {
                direction ++;
                direction %= 4;
            }
        }
    }
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            printf("%c", map[r][c]);
        }
        printf("\n");
    }
    printf("%d\n", count);
}