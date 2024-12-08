#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT 

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 12
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 50
#endif

typedef struct {
    int r;
    int c;
} Position;

typedef struct {
    char freq;
    int count;
    Position antennas[100];
} Frequency;

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char map[SIZE][SIZE];

    Frequency frequencyTable[256] = {0};

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            fscanf(f, "%c ", &map[r][c]);
            if (map[r][c] != '.') {
                frequencyTable[map[r][c]].freq = map[r][c];
                frequencyTable[map[r][c]].antennas[frequencyTable[map[r][c]].count] = (Position){r,c};
                frequencyTable[map[r][c]].count ++;
            }
        }
    }
    for (int i = 0; i < 256; i++) {
        Frequency freq = frequencyTable[i];
        if (freq.freq != 0) {
            for (int j = 0; j < freq.count-1; j++) {
                Position a = freq.antennas[j];
                for (int k = j+1; k < freq.count; k++) {
                    Position b = freq.antennas[k];
                    int diffRow = b.r - a.r;
                    int diffCol = b.c - a.c;
                    Position c = {a.r - diffRow, a.c - diffCol};
                    Position d = {b.r + diffRow, b.c + diffCol};
                    if (c.r >= 0 && c.r < SIZE && c.c >= 0 && c.c < SIZE) {
                        map[c.r][c.c] = '#';
                    }
                    if (d.r >= 0 && d.r < SIZE && d.c >= 0 && d.c < SIZE) {
                        map[d.r][d.c] = '#';
                    }
                }
            }
        }
    }
    int count = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            printf("%c", map[r][c]);
            if (map[r][c] == '#') {
                count ++;
            }
        }
        printf("\n");
    }
    printf("%d\n", count);
}