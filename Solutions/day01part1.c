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

    qsort(list1, SIZE, sizeof(int), compare);
    qsort(list2, SIZE, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        int diff = abs(list1[i] - list2[i]);
        printf("abs(%d - %d) = %d\n", list1[i], list2[i], diff);
        sum += diff;

    }
    printf("%d\n", sum);
}