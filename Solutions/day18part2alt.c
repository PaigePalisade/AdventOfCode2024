#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 7
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 71
#endif

// BFS
// Made faster with binary search
// Time improvement of 0.002s vs  0.864s

typedef struct Position Position;

struct Position {
    int r;
    int c;
    int d;
    Position* next;
};

typedef struct {
    int r;
    int c;
} Obstacle;

Position* start = NULL;
Position* end;

int checkForPath(int time);
void insertQueue(int r, int c, int d);
Position popQueue();
void resetQueue();

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
    int low = 0;
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
}

// checks for available paths at a given time
int checkForPath(int time) {
    resetQueue();
    insertQueue(0, 0, 0);
    int visited[SIZE][SIZE] = {0};

    while (start != NULL) {
        Position p = popQueue();
        if (map[p.r][p.c] <= time || visited[p.r][p.c]) {
            continue;
        }
        if (p.r == SIZE-1 && p.c == SIZE-1) {
            return 1;
        }
        visited[p.r][p.c] = 1;
        if (p.r+1 < SIZE) {
            insertQueue(p.r+1, p.c, p.d+1);
        }
        if (p.r-1 >= 0) {
            insertQueue(p.r-1, p.c, p.d+1);
        }
        if (p.c+1 < SIZE) {
            insertQueue(p.r, p.c+1, p.d+1);
        }
        if (p.c-1 >= 0) {
            insertQueue(p.r, p.c-1, p.d+1);
        }
    }
    return 0;
}

void insertQueue(int r, int c, int d) {
    Position* p = (Position*)malloc(sizeof(Position));
    p->r = r;
    p->c = c;
    p->d = d;
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