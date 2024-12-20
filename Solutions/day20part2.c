#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 15
#define CUTOFF 50
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 141
#define CUTOFF 100
#endif

#define MAX_CHEAT 20

int getCheatsFromPoint(int r, int c);

char map[SIZE][SIZE];
int dist[SIZE][SIZE];

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    // start row, column
    int sr;
    int sc;

    // end row, column
    int er;
    int ec;

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
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (map[r][c] != '#') {
                numCheats += getCheatsFromPoint(r, c);
            }
        }
    }

    printf("%d\n", numCheats);
}

// a cheat is two points with a taxicab distance at most 20 (MAX_CHEAT) which saves time
int getCheatsFromPoint(int r, int c) {
    int result = 0;
    for (int i = -MAX_CHEAT; i <= MAX_CHEAT; i++) {
        for (int j = -MAX_CHEAT; j <= MAX_CHEAT; j++) {
            int cheatLen = abs(i) + abs(j);
            if (cheatLen <= MAX_CHEAT && r+i < SIZE && r+i >= 0 && c+j < SIZE && c+j >= 0 && map[r+i][c+j] != '#') {
                int d1 = dist[r][c];
                int d2 = dist[r+i][c+j];
                int saved = 0;
                if (d1 + cheatLen < d2) {
                    saved = d2 - (d1+cheatLen);
                }
                if (saved >= CUTOFF) {
                    result ++;
                }
            }
        }
    }
    return result;
}