#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 140

char map[SIZE][SIZE+1];

int main() {
    FILE* f = fopen("input.txt", "r");

    for (int i = 0; i < SIZE; i++) {
        fscanf(f, "%s ", &map[i]);
    }

    int count = 0;

    for (int i = 0; i <= SIZE-3; i++) {
        for (int j = 0; j <= SIZE-3; j++) {
            int valid = 0;
            if (map[i+1][j+1] == 'A') {
                valid = 1;
                if (!((map[i][j] == 'M' && map[i+2][j+2] == 'S') || (map[i][j] == 'S' && map[i+2][j+2] == 'M'))) {
                    valid = 0;
                }
                if (!((map[i+2][j] == 'M' && map[i][j+2] == 'S') || (map[i+2][j] == 'S' && map[i][j+2] == 'M'))) {
                    valid = 0;
                }
            }
            count += valid;
        }
    }

    printf("%d\n", count);
}