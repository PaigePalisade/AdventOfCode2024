// Alternative solution for Day 5 Part 2 using qsort
// this has a lower time complexity matching quick sort in reguards to n=length of line O(n log n)
// and a lower runtime (0.003s vs 0.29s)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 

#ifdef TEST
#define FILE_NAME "test.txt"
#define NUM_RULES 21
#define NUM_LINES 6
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define NUM_RULES 1176
#define NUM_LINES 202
#endif

int ruleMatrix[100][100] = {0};

int cmpfunc(const void *p1, const void *p2) {
    int a = *(int*)p1;
    int b = *(int*)p2;
    if (ruleMatrix[a][b]) {
        return -1;
    }
    if (ruleMatrix[b][a]) {
        return 1;
    }
    return 0;
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    for (int i = 0; i < NUM_RULES; i++) {
        int a,b;
        fscanf(f, "%d|%d ", &a, &b);
        ruleMatrix[a][b] = 1;
    }

    int sum = 0;
    for (int i = 0; i < NUM_LINES; i++) {
        int count = 0;
        int line[100] = {0};

        char delim;
        do {
            fscanf(f, "%d%c", &line[count], &delim);
            count ++;
        } while (delim == ',' && !feof(f));

        int lineSorted[100];
        memcpy(lineSorted, line, count * sizeof(int));

        qsort(lineSorted, count, sizeof(int), cmpfunc);

        if (memcmp(line, lineSorted, count * sizeof(int)) != 0) {
            sum += lineSorted[count/2];
        }
    }

    printf("%d\n", sum);
}