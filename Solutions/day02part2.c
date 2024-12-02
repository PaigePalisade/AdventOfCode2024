#include <stdio.h>
#include <stdlib.h>

#define NUM_REPORTS 1000

// NOTE: modified input to have trailing newline

int check(int* report, int reportLen, int toSkip) {
    int copy[100];
    for (int i = 0; i < reportLen-1; i++) {
        if (i < toSkip) {
            copy[i] = report[i];
        }
        else {
            copy[i] = report[i+1];
        }
    }
    reportLen --;
    int isIncreasing = 1;
    int isDecreasing = 1;
    for (int i = 0; i < reportLen-1; i++) {
        if (copy[i+1] <= copy[i]) {
            isIncreasing = 0;
        }
        if (copy[i+1] >= copy[i]) {
            isDecreasing = 0;
        }
        if (abs(copy[i+1] - copy[i]) > 3) {
            isIncreasing = 0;
            isDecreasing = 0;
        }
    }
    return (isIncreasing || isDecreasing);
}

int main() {
    FILE* f = fopen("input.txt", "r");

    int count = 0;

    for (int i = 0; i < NUM_REPORTS; i++) {
        int report[100];
        int reportLen = 0;
        char delim = ' ';
        while (delim != '\n') {
            fscanf(f, "%d", &report[reportLen]);
            reportLen ++;
            fscanf(f, "%c", &delim);
        }
        int safe = 0;

        for (int j = 0; j < reportLen; j++) {
            if (check(report, reportLen, j)) {
                safe = 1;
            }
        }

        for (int j = 0; j < reportLen; j++) {
            printf("%d ", report[j]);
        }
        if (safe) {
            printf("safe");
        }
        printf("\n");

        count += safe;
    }
    printf("%d\n", count);
}