#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 15
#define CUTOFF 1
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 141
#define CUTOFF 100
#endif

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    // start row, column
    int sr;
    int sc;

    // end row, column
    int er;
    int ec;

    char map[SIZE][SIZE];
    int dist[SIZE][SIZE];

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            fscanf(f, "%c ", &map[r][c]);
            dist[r][c] = -1;
            if (map[r][c] == 'S') {
                sr = r;
                sc = c;
            }
            if (map[r][c] == 'E') {
                er = r;
                ec = c;
            }
        }
    }

    int r = sr;
    int c = sc;
    int d = 0;

    // map is guaranteed to not have forks, pathfinding is not required
    while (r != er || c != ec) {
        dist[r][c] = d;
        if (r-1 >= 0 && map[r-1][c] != '#' && dist[r-1][c] == -1) {
            r --;
        }
        else if (c+1 < SIZE && map[r][c+1] != '#' && dist[r][c+1] == -1) {
            c ++;
        }
        else if (r+1 < SIZE && map[r+1][c] != '#' && dist[r+1][c] == -1) {
            r ++;
        }
        else if (c-1 >= 0 && map[r][c-1] != '#' && dist[r][c-1] == -1) {
            c --;
        }
        d++;
    }
    dist[er][ec] = d;

    int numCheats = 0;

    // check for cheats
    // a cheat is a .#. pattern horizontally or vertically where . can also be S or E
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (c+2 < SIZE && map[r][c] != '#' && map[r][c+1] == '#' && map[r][c+2] != '#') {
                int saved;
                if (dist[r][c] < dist[r][c+2]) {
                    saved = dist[r][c+2] - (dist[r][c] + 2);
                }
                else {
                    saved = dist[r][c] - (dist[r][c+2] + 2);
                }
                if (saved >= CUTOFF) {
                    numCheats ++;
                }
            }
            if (r+2 < SIZE && map[r][c] != '#' && map[r+1][c] == '#' && map[r+2][c] != '#') {
                int saved;
                if (dist[r][c] < dist[r+2][c]) {
                    saved = dist[r+2][c] - (dist[r][c] + 2);
                }
                else {
                    saved = dist[r][c] - (dist[r+2][c] + 2);
                }
                if (saved >= CUTOFF) {
                    numCheats ++;
                }
            }
        }
    }
    printf("%d\n", numCheats);
}