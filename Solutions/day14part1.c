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

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long q1, q2, q3, q4 = 0;

    for (int i = 0; i < NUM_ROBOTS; i++) {
        int px, py, vx, vy;

        fscanf(f, "p=%d,%d v=%d,%d ", &px, &py, &vx, &vy);
        px = mod((px + vx * 100), WIDTH);
        py = mod((py + vy * 100), HEIGHT);
        
        if (px < WIDTH / 2 && py < HEIGHT / 2) {
            q1 ++;
        }
        if (px > WIDTH / 2 && py < HEIGHT / 2) {
            q2 ++;
        }
        if (px < WIDTH / 2 && py > HEIGHT / 2) {
            q3 ++;
        }
        if (px > WIDTH / 2 && py > HEIGHT / 2) {
            q4 ++;
        }
    }

    long safety = q1 * q2 * q3 * q4;

    printf("%d\n%d\n%d\n%d\n", q1, q2, q3, q4);

    printf("%ld\n", safety);
}

// C mishandles modulo with negative numbers
int mod(int a, int b) {
    int result = a % b;
    if (result < 0) {
        result += b;
    }
    return result;
}