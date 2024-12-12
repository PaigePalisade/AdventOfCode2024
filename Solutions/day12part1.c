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

// uses a floodfill algorithm to mark the shapes with different ID's
// then uses a raycasting algorithm to calculate the perimeter and area
// the raycast can tell if it hits the perimter if there is a change between shapes or the wall

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

    // sum areas and perimeters
    int sum = 0;
    for (int i = 1; i < shapeID; i++) {
        sum += getPrice(i);
    }

    printf("%d\n", sum);
}

void floodFill(int r, int c, int id) {
    // uses DFS because that's easier for me
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
    int perimeter = 0;
    int area = 0;

    // horizontal raycast for horizontal perimeter and total area
    for (int r = 0; r < SIZE; r++) {
        int inShape = 0;
        for (int c = 0; c < SIZE; c++) {
            if (shapes[r][c] == id) {
                area ++;
                if (!inShape) {
                    inShape = 1;
                    perimeter ++;
                }
            }
            else if (inShape) {
                inShape = 0;
                perimeter ++;
            }
        }
        if (inShape) {
            perimeter ++;
        }
    }

    // vertical raycast for vertical perimeter
    for (int c = 0; c < SIZE; c++) {
        int inShape = 0;
        for (int r = 0; r < SIZE; r++) {
            if (shapes[r][c] == id) {
                if (!inShape) {
                    inShape = 1;
                    perimeter ++;
                }
            }
            else if (inShape) {
                inShape = 0;
                perimeter ++;
            }
        }
        if (inShape) {
            perimeter ++;
        }
    }
    printf("%d * %d = %d\n", area, perimeter, perimeter * area);
    return perimeter * area;
}