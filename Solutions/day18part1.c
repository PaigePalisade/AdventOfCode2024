#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

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

// BFS

typedef struct Position Position;

struct Position {
    int r;
    int c;
    int d;
    Position* next;
};

Position* start = NULL;
Position* end;

void insertQueue(int r, int c, int d);
Position popQueue();

int map[SIZE][SIZE] = {0};

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    for (int i = 0; i < COUNT; i++) {
        int r, c;
        fscanf(f, "%d,%d ", &c, &r);
        map[r][c] = 1;
    }

    insertQueue(0, 0, 0);
    int visited[SIZE][SIZE] = {0};

    int distance;

    while (start != NULL) {
        Position p = popQueue();
        if (map[p.r][p.c] || visited[p.r][p.c]) {
            continue;
        }
        if (p.r == SIZE-1 && p.c == SIZE-1) {
            distance = p.d;
            break;
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
    printf("%d\n", distance);
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