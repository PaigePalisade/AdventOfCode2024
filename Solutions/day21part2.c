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

#define LAYERS 26

void findChar(int* row, int* col, char pad[4][4], char chr);
long getCost(char start, char end, char pad[4][4], int depth);
long min(long a, long b);

enum directions {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE
};

char numPad[4][4] = {
    "789",
    "456",
    "123",
    "-0A"
};

char directionalPad[4][4] = {
    "-^A",
    "<v>",
    "---",
    "---"
};

long costArr[4][4][4][4][LAYERS];

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    // initialize cost array
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    for (int m = 0; m < LAYERS; m++) {
                        costArr[i][j][k][l][m] = -1;
                    }
                }
            }
        }
    }

    long sum;
    for (int i = 0; i < 5; i++) {
        char str[5];
        fscanf(f, "%s ", str);
        int chr = 'A';
        long cost = 0;
        for (int j = 0; j < 4; j++) {
            cost += getCost(chr, str[j], numPad, 0);
            chr = str[j];
        }
        int num = atoi(str);
        sum += cost * num;
        printf("%s: %ld\n", str, cost);
    }
    printf("%ld\n", sum);
}

long getCost(char start, char end, char pad[4][4], int depth) {
    // the final keypad has no cost
    if (depth == LAYERS) {
        return 1;
    }

    int startRow, startCol;
    int endRow, endCol;
    findChar(&startRow, &startCol, pad, start);
    findChar(&endRow, &endCol, pad, end);

    // check if cost was already calculated

    if (costArr[startRow][startCol][endRow][endCol][depth] != -1) {
        return costArr[startRow][startCol][endRow][endCol][depth];
    }
    
    long result = __LONG_MAX__;

    // get the cost of horizontal-vertical
    long horizVert = 0;
    if (pad[startRow][endCol] != '-') {
        char first = 'A';
        char second;
        if (endCol < startCol) {
            horizVert += getCost('A', '<', directionalPad, depth + 1);
            horizVert += getCost('<', '<', directionalPad, depth + 1) * (startCol - endCol - 1);
            first = '<';
        }
        if (endCol > startCol) {
            horizVert += getCost('A', '>', directionalPad, depth + 1);
            horizVert += getCost('>', '>', directionalPad, depth + 1) * (endCol - startCol - 1);
            first = '>';
        }
        second = first;
        if (endRow < startRow) {
            horizVert += getCost(first, '^', directionalPad, depth + 1);
            horizVert += getCost('^', '^', directionalPad, depth + 1) * (startRow - endRow - 1);
            second = '^';
        }
        if (endRow > startRow) {
            horizVert += getCost(first, 'v', directionalPad, depth + 1);
            horizVert += getCost('v', 'v', directionalPad, depth + 1) * (endRow - startRow - 1);
            second = 'v';
        }
        horizVert += getCost(second, 'A', directionalPad, depth + 1);
        result = min(result, horizVert);
    }

    // get the cost of vertical-horizontal
    long vertHoriz = 0;
    if (pad[endRow][startCol] != '-') {
        char first = 'A';
        char second;
        if (endRow < startRow) {
            vertHoriz += getCost('A', '^', directionalPad, depth + 1);
            vertHoriz += getCost('^', '^', directionalPad, depth + 1) * (startRow - endRow - 1);
            first = '^';
        }
        if (endRow > startRow) {
            vertHoriz += getCost('A', 'v', directionalPad, depth + 1);
            vertHoriz += getCost('v', 'v', directionalPad, depth + 1) * (endRow - startRow - 1);
            first = 'v';
        }
        second = first;
        if (endCol < startCol) {
            vertHoriz += getCost(first, '<', directionalPad, depth + 1);
            vertHoriz += getCost('<', '<', directionalPad, depth + 1) * (startCol - endCol - 1);
            second = '<';
        }
        if (endCol > startCol) {
            vertHoriz += getCost(first, '>', directionalPad, depth + 1);
            vertHoriz += getCost('>', '>', directionalPad, depth + 1) * (endCol - startCol - 1);
            second = '>';
        }
        vertHoriz += getCost(second, 'A', directionalPad, depth + 1);
        result = min(result, vertHoriz);
    }

    // return minimum cost
    assert(result != __LONG_MAX__);
    assert(result > 0);
    costArr[startRow][startCol][endRow][endCol][depth] = result;
    return result;
}

void findChar(int* row, int* col, char pad[4][4], char chr) {
    *row = -1;
    *col = -1;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (pad[r][c] == chr) {
                *row = r;
                *col = c;
            }
        }
    }
    assert(*row != -1 && *col != -1);
}

long min(long a, long b) {
    if (a < b) {
        return a;
    }
    return b;
}