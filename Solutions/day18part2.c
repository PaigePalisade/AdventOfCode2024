#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CHALLENGE

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 7
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 71
#endif

#ifdef CHALLENGE
#define FILE_NAME "challenge.txt"
#define SIZE 213
#endif

// BFS
// Could be made faster by binary searching

typedef struct Position Position;

struct Position {
    int r;
    int c;
    int d;
    Position* next;
};

Position* start = NULL;
Position* end;

int checkForPath();
void insertQueue(int r, int c, int d);
Position popQueue();
void resetQueue();

int map[SIZE][SIZE] = {0};

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    while (!feof(f)) {
        int r, c;
        fscanf(f, "%d,%d ", &c, &r);
        map[r][c] = 1;
        if (!checkForPath()) {
            printf("%d,%d\n", c, r);
            break;
        }
    }
}

int checkForPath() {
    resetQueue();
    insertQueue(0, 0, 0);
    int visited[SIZE][SIZE] = {0};

    while (start != NULL) {
        Position p = popQueue();
        if (map[p.r][p.c] || visited[p.r][p.c]) {
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