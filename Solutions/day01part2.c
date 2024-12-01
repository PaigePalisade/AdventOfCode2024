#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int compare(const void* a, const void*b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    FILE* f = fopen("input.txt", "r");

    int list1[SIZE];
    int list2[SIZE];

    for (int i = 0; i < SIZE; i++) {
        fscanf(f, "%d %d ", &list1[i], &list2[i]);
    }

    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (list1[i] == list2[j]) {
                count ++;
            }
        }
        sum += count * list1[i];

    }
    printf("%d\n", sum);
}