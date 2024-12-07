#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT 

#ifdef TEST
#define FILE_NAME "test.txt"
#define SIZE 9
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define SIZE 850
#endif

long concat(long a, long b) {
    assert(a > 0 && b > 0);
    long biggestDigit = 1;
    while (b >= biggestDigit) {
        biggestDigit *= 10;
    }
    assert(a * biggestDigit + b > 0);
    return a * biggestDigit + b;
}

int check(long* nums, int numCount, long target, long value) {
    if (numCount == 0) {
        if (value == target) {
            return 1;
        }
        return 0;
    }
    if (value > target) {
        return 0;
    }
    assert(value > 0);
    return check(&nums[1], numCount - 1, target, value + nums[0]) ||
           check(&nums[1], numCount - 1, target, value * nums[0]) ||
           check(&nums[1], numCount - 1, target, concat(value, nums[0]));
}

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long sum = 0;
    for (int i = 0; i < SIZE; i++) {
        long target;
        long nums[100];
        int numCount = 0;
        char delim = ' ';

        fscanf(f, "%ld: ", &target);
        while (delim == ' ' && !feof(f)) {
            fscanf(f, "%ld%c", &nums[numCount], &delim);
            numCount ++;
        }
        int valid = check(&nums[1], numCount - 1, target, nums[0]);
        printf("%ld: ", target);
        for (int j = 0; j < numCount; j++) {
            printf("%ld ", nums[j]);
        }
        if (valid) {
            printf("valid");
            sum += target;
        }
        assert(sum >= 0);
        printf("\n");
    }
    printf("%ld\n", sum);
}