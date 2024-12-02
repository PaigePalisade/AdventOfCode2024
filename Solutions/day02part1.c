#include <stdio.h>
#include <stdlib.h>

#define NUM_REPORTS 1000

// NOTE: modified input to have trailing newline

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
        int increasing = (report[1] - report[0]) > 0;
        int safe = 1;
        if (report[1] - report[0] == 0) {
            safe = 0;
        }
        for (int j = 0; j < reportLen-1; j++) {
            if (increasing && !(report[j+1] > report[j])) {
                safe = 0;
            }
            if (!increasing && !(report[j+1] < report[j])) {
                safe = 0;
            }
            if (abs(report[j+1] - report[j]) > 3) {
                safe = 0;
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