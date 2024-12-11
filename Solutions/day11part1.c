#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#endif

// uses a naive linked list approach where the rules are applied 25 times and then the final stones are counted

typedef struct Stone Stone;

struct Stone {
    long value;
    Stone* next;
};

int numDigits(long n);
void printList(Stone* start);

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    Stone start = {0};
    Stone* end = &start;

    // read input
    while (!feof(f)) {
        long num;
        fscanf(f, "%ld ", &num);
        end->value = num;
        if (!feof(f)) {
            Stone* newEnd = (Stone*)calloc(1, sizeof(Stone));
            end->next = newEnd;
            end = newEnd;
        }
    }

    // process stones
    // printList(&start);
    for (int i = 0; i < 25; i++) {
        Stone* s = &start;
        while (s != NULL) {
            Stone* next = s->next;
            if (s->value == 0) {
                s->value = 1;
            }
            else {
                int digits = numDigits(s->value);
                if (digits % 2 == 0) {
                    long place = 1;
                    for (int j = 0; j < digits/2; j++) {
                        place *= 10;
                    }
                    long num1 = s->value / place;
                    long num2 = s->value % place;
                    s->value = num1;
                    Stone* newNode = (Stone*)calloc(1, sizeof(Stone));
                    newNode->value = num2;
                    newNode->next = s->next;
                    s->next = newNode;
                }
                else {
                    s->value *= 2024;
                }
            }
            s = next;
        }
        // printList(&start);
    }

    // count stones and free memory
    int count = 1;
    Stone* s = start.next;
    while (s != NULL) {
        Stone* next = s->next;
        count ++;
        free(s);
        s = next;
    }
    printf("%d\n", count);
}

// counts the number of digits in a number
int numDigits(long n) {
    int digits = 0;
    while (n != 0) {
        n /= 10;
        digits ++;
    }
    return digits;
}

// prints the linked list for debugging
void printList(Stone* start) {
    for (Stone* s = start; s != NULL; s = s->next) {
        printf("%ld ", s->value);
    }
    printf("\n");
}