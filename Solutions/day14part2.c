#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define NUM_ROBOTS 12
#define WIDTH 11
#define HEIGHT 7
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define NUM_ROBOTS 500
#define WIDTH 101
#define HEIGHT 103
#endif

int mod(int a, int b);

typedef struct {
    int px;
    int py;
    int vx;
    int vy;
} Robot;

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long q1, q2, q3, q4 = 0;

    Robot robots[NUM_ROBOTS];

    for (int i = 0; i < NUM_ROBOTS; i++) {
        int px, py, vx, vy;

        fscanf(f, "p=%d,%d v=%d,%d ", &px, &py, &vx, &vy);

        robots[i] = (Robot){px, py, vx, vy};
    }


    // I noticed that the map got jumbled at 113, 214, 315, etc.
    // So, I only checked those ones
    // the first tree I saw by randomly scrolling was too high, so I just set that as the upper bound and looked again
    for (int t = 113; t < 37786; t+=101) {
        int map[WIDTH][HEIGHT] = {0};
        printf("%d\n", t);
        for (int i = 0; i < NUM_ROBOTS; i++) {
            int px = mod(robots[i].px + robots[i].vx * t, WIDTH);
            int py = mod(robots[i].py + robots[i].vy * t, HEIGHT);
            map[px][py] = 1;
        }
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (map[x][y]) {
                    printf("#");
                }
                else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
}

// C mishandles modulo with negative numbers
int mod(int a, int b) {
    int result = a % b;
    if (result < 0) {
        result += b;
    }
    return result;
}