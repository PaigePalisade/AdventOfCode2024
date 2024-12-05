#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

typedef struct {
    int a;
    int b;
} Rule;

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    Rule rules[NUM_RULES];

    for (int i = 0; i < NUM_RULES; i++) {
        int a,b;
        fscanf(f, "%d|%d ", &a, &b);
        rules[i].a = a;
        rules[i].b = b;
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

        int incorrect = 1;
        int valid = 0;
        // seemingly, applying the rules once isn't enough
        while (incorrect) {
            incorrect = 0;
            for (int j = 0; j < NUM_RULES; j++) {
                // if only a or b is in the line or if neither of them are in the line, a_pos < b_pos
                int a_pos = -1;
                int b_pos = 1000;

                for (int k = 0; k < count; k++) {
                    if (line[k] == rules[j].a) {
                        a_pos = k;
                    }
                    if (line[k] == rules[j].b) {
                        b_pos = k;
                    }
                }
                if (a_pos > b_pos) {
                    int temp = line[a_pos];
                    line[a_pos] = line[b_pos];
                    line[b_pos] = temp;
                    incorrect = 1;
                    valid = 1;
                }
            }
        }
        int midpoint = line[count/2];
        sum += midpoint * valid;
    }

    printf("%d\n", sum);
}