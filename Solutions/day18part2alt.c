#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEST

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 7
#define COUNT 12
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 71
#define COUNT 1024
#endif

#ifdef CHALLENGE
#define FILE_NAME "challenge.txt"
#define SIZE 213
#define COUNT 1024
#endif

// BFS
// Made faster with binary search
// Time improvement of 0.039s vs 50.509s using O3 optimization on u/paul_SB76's challenge input

typedef struct Position Position;

struct Position {
    int r;
    int c;
    int d;
    int minTime;
    Position* next;
};

typedef struct {
    int r;
    int c;
} Obstacle;

Position* start = NULL;
Position* end;

int checkForPath(int time);
void insertQueue(int r, int c, int d, int minTime);
Position popQueue();
void resetQueue();
int min(int a, int b);
int max(int a, int b);

// safeTime stores the maximum time known to be safe
// this only reduces calls of the function from 15 to 12 in the challenge input
int safeTime = 0;
int calls = 0;

// contains the time of which each obstacle will fall or __INT_MAX__ if an obstacle will never fall there
int map[SIZE][SIZE];

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            map[r][c] = __INT_MAX__;
        }
    }
    
    // contains the obstacle added at any given time
    Obstacle obstacles[SIZE*SIZE];
    int numObstacles;

    while (!feof(f)) {
        int r, c;
        fscanf(f, "%d,%d ", &c, &r);
        map[r][c] = numObstacles;
        obstacles[numObstacles++] = (Obstacle){r,c};
    }

    // binary search
    int low = COUNT;
    int high = numObstacles - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (!checkForPath(mid)) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    printf("%d,%d\n", obstacles[low].c, obstacles[low].r);
    printf("%d\n", calls);
}

// checks for available paths at a given time
int checkForPath(int time) {
    if (time <= safeTime) {
        return 1;
    }
    calls ++;
    resetQueue();
    insertQueue(0, 0, 0, __INT_MAX__);
    int visited[SIZE][SIZE] = {0};

    while (start != NULL) {
        Position p = popQueue();
        if (map[p.r][p.c] <= time || visited[p.r][p.c]) {
            continue;
        }
        if (p.r == SIZE-1 && p.c == SIZE-1) {
            safeTime = max(safeTime, p.minTime-1);
            return 1;
        }
        visited[p.r][p.c] = 1;
        p.minTime = min(p.minTime, map[p.r][p.c]);
        if (p.r+1 < SIZE) {
            insertQueue(p.r+1, p.c, p.d+1, p.minTime);
        }
        if (p.r-1 >= 0) {
            insertQueue(p.r-1, p.c, p.d+1, p.minTime);
        }
        if (p.c+1 < SIZE) {
            insertQueue(p.r, p.c+1, p.d+1, p.minTime);
        }
        if (p.c-1 >= 0) {
            insertQueue(p.r, p.c-1, p.d+1, p.minTime);
        }
    }
    return 0;
}

void insertQueue(int r, int c, int d, int minTime) {
    Position* p = (Position*)malloc(sizeof(Position));
    p->r = r;
    p->c = c;
    p->d = d;
    p->minTime = minTime;
    p->next = NULL;
    if (start == NULL) {
        start = p;
        end = p;
    }
    else {
        end->next = p;
        end = p;
    }
}
Position popQueue() {
    Position result;
    Position* p = start;
    assert(p != NULL);
    start = p->next;
    result.r = p->r;
    result.c = p->c;
    result.d = p->d;
    result.minTime = p->minTime;
    result.next = NULL;
    free(p);
    return result;
}

void resetQueue() {
    while (start != NULL) {
        popQueue();
    }
    end = NULL;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}