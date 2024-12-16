#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 15
#endif

#ifdef TEST2
#define FILE_NAME "test2.txt"
#define SIZE 17
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 141
#endif

// calculates the result for part 1, then uses a dfs to mark all possible paths of the minimum length

enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct {
    int r;
    int c;
    int direction;
    int score;
} Move;

int min(int a, int b);
int mod(int a, int b);
void insertQueue(Move m);
Move popQueue();
int markPathsOfScore(int r, int c, int direction, int score, int target);

Move moveQueue[SIZE*SIZE*20];
int queueSize = 0;
char map[SIZE][SIZE];
int seatMap[SIZE][SIZE] = {0};
int minDistance[SIZE][SIZE][4];

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // start row, start column
    int sr, sc;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            fscanf(f, "%c ", &map[r][c]);
            for (int d = 0; d < 4; d++) {
                minDistance[r][c][d] = __INT_MAX__;
            }
            if (map[r][c] == 'S') {
                sr = r;
                sc = c;
            }
        }
    }

    insertQueue((Move){sr, sc, EAST, 0});

    int score;

    while (queueSize != 0) {
        Move bestMove = popQueue();
        int r = bestMove.r;
        int c = bestMove.c;
        int direction = bestMove.direction;
        score = bestMove.score;
        if (map[r][c] == 'E') {
            break;
        }
        if (map[r][c] == '#') {
            continue;
        }
        if (score >= minDistance[r][c][direction]) {
            continue;
        }
        minDistance[r][c][direction] = score;
        insertQueue((Move){r, c, mod(direction+1,4),score+1000});
        insertQueue((Move){r, c, mod(direction-1,4),score+1000});
        if (direction == NORTH) {
            insertQueue((Move){r-1, c, direction, score+1});
        }
        if (direction == EAST) {
            insertQueue((Move){r, c+1, direction, score+1});
        }
        if (direction == SOUTH) {
            insertQueue((Move){r+1, c, direction, score+1});
        }
        if (direction == WEST) {
            insertQueue((Move){r, c-1, direction, score+1});
        }

    }
    printf("%d\n", score);
    // Part 2 starts here
    int numSeats = 0;
    markPathsOfScore(sr, sc, EAST, 0, score);
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (seatMap[r][c]) {
                printf("O");
                numSeats ++;
            }
            else {
                printf("%c", map[r][c]);
            }
        }
        printf("\n");
    }
    printf("%d\n", numSeats);
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

// C mishandles modulo with negative numbers
int mod(int a, int b) {
    int result = a % b;
    if (result < 0) {
        result += b;
    }
    return result;
}

int markPathsOfScore(int r, int c, int direction, int score, int target) {
    if (score == target && map[r][c] == 'E') {
        seatMap[r][c] = 1;
        return 1;
    }
    if (score >= target) {
        return 0;
    }
    if (map[r][c] == '#') {
        return 0;
    }
    // in Dijkstra, we calculated the minimum score for a row, column, direction so if we are above that, we are not on a best path
    if (score > minDistance[r][c][direction]) {
        return 0;
    }
    minDistance[r][c][direction] = score;
    int isBestPath = 0;
    if (direction == NORTH) {
        isBestPath = markPathsOfScore(r-1, c, direction, score+1, target);
    }
    if (direction == EAST) {
        isBestPath = markPathsOfScore(r, c+1, direction, score+1, target);
    }
    if (direction == SOUTH) {
        isBestPath = markPathsOfScore(r+1, c, direction, score+1, target);
    }
    if (direction == WEST) {
        isBestPath = markPathsOfScore(r, c-1, direction, score+1, target);
    }
    if (markPathsOfScore(r, c, mod(direction+1,4), score+1000, target)) {
        isBestPath = 1;
    }
    if (markPathsOfScore(r, c, mod(direction-1,4), score+1000, target)) {
        isBestPath = 1;
    }
    
    if (isBestPath) {
        seatMap[r][c] = 1;
    }
    return isBestPath;
}

void shiftUp(int index) {
    while (index > 0 && moveQueue[(index - 1) / 2].score > moveQueue[index].score) {
        Move temp = moveQueue[index];
        moveQueue[index] = moveQueue[(index - 1) / 2];
        moveQueue[(index - 1) / 2] = temp;
        index = (index-1)/2;
    }
}

void shiftDown(int index) {
    int minIndex = index;

    int left = ((2 * index) + 1);
    int right = ((2 * index) + 2);

    if (left < queueSize && moveQueue[left].score < moveQueue[minIndex].score) {
        minIndex = left;
    }
    if (right < queueSize && moveQueue[right].score < moveQueue[minIndex].score) {
        minIndex = right;
    }
    if (minIndex != index) {
        Move temp = moveQueue[index];
        moveQueue[index] = moveQueue[minIndex];
        moveQueue[minIndex] = temp;
        shiftDown(minIndex);
    }
}

void insertQueue(Move m) {
    moveQueue[queueSize] = m;

    int index = queueSize;
    queueSize ++;

    shiftUp(index);
}

Move popQueue() {
    Move result = moveQueue[0];

    moveQueue[0] = moveQueue[queueSize-1];
    queueSize --;

    shiftDown(0);

    return result;
}

