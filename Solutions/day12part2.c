#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 10
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 140
#endif

// same method as part 1

char map[SIZE][SIZE];

int shapes[SIZE][SIZE] = {0};

void floodFill(int r, int c, int ID);

int getPrice(int id);

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    int shapeID = 1;
    
    // get input
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            fscanf(f, "%c ", &map[r][c]);
        }
    }

    // mark shapes
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (shapes[r][c] == 0) {
                floodFill(r, c, shapeID);
                shapeID ++;
            }
        }
    }

    // sum sides and areas
    int sum = 0;
    for (int i = 1; i < shapeID; i++) {
        sum += getPrice(i);
    }

    printf("%d\n", sum);
}

void floodFill(int r, int c, int id) {
    shapes[r][c] = id;

    if (r+1 < SIZE && shapes[r+1][c] == 0 && map[r+1][c] == map[r][c]) {
        floodFill(r+1, c, id);
    }
    if (r-1 >= 0 && shapes[r-1][c] == 0 && map[r-1][c] == map[r][c]) {
        floodFill(r-1, c, id);
    }
    if (c+1 < SIZE && shapes[r][c+1] == 0 && map[r][c+1] == map[r][c]) {
        floodFill(r, c+1, id);
    }
    if (c-1 >= 0 && shapes[r][c-1] == 0 && map[r][c-1] == map[r][c]) {
        floodFill(r, c-1, id);
    }
}

int getPrice(int id) {
    int sides = 0;
    int area = 0;

    // if casting left/right:
    // a perimter edge is in the same side if there was a perimeter edge in the previous row
    // whether that edge is inShape to !inShape or !inShape to inShape matters
    // !inShape to inShape is stored as a 1 and inShape to !inShape is stored as a 2

    int horizChanges[SIZE][SIZE+1] = {0};
    int vertChanges[SIZE+1][SIZE] = {0};

    // horizontal raycast for horizontal sides and total area
    for (int r = 0; r < SIZE; r++) {
        int inShape = 0;
        for (int c = 0; c < SIZE; c++) {
            if (shapes[r][c] == id) {
                area ++;
                if (!inShape) {
                    inShape = 1;
                    horizChanges[r][c] = 1;
                    if (r == 0 || horizChanges[r-1][c] != 1) {
                        sides ++;
                    }
                }
            }
            else if (inShape) {
                inShape = 0;
                horizChanges[r][c] = 2;
                if (r == 0 || horizChanges[r-1][c] != 2) {
                    sides ++;
                }
            }
        }
        if (inShape) {
            horizChanges[r][SIZE] = 2;
            if (r == 0 || horizChanges[r-1][SIZE] != 2) {
                sides ++;
            }
        }
    }

    // vertical raycast for vertical sides
    for (int c = 0; c < SIZE; c++) {
        int inShape = 0;
        for (int r = 0; r < SIZE; r++) {
            if (shapes[r][c] == id) {
                if (!inShape) {
                    inShape = 1;
                    vertChanges[r][c] = 1;
                    if (c == 0 || vertChanges[r][c-1] != 1) {
                        sides ++;
                    }
                }
            }
            else if (inShape) {
                inShape = 0;
                vertChanges[r][c] = 2;
                if (c == 0 || vertChanges[r][c-1] != 2) {
                    sides ++;
                }
            }
        }
        if (inShape) {
            vertChanges[SIZE][c] = 2;
            if (c == 0 || vertChanges[SIZE][c-1] != 2) {
                sides ++;
            }
        }
    }
    printf("%d * %d = %d\n", area, sides, sides * area);
    return sides * area;
}