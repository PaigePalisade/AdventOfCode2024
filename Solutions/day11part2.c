#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// GLIBC's built in hash table
#include <search.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#endif

// uses a recursive solution and a hash table based memoization
// each time the recursive function is called, I check to see if it has been called before with the same params
// if so, it returns that result
// if not, it continues and adds the calcualed result to the hash table before returning

// too debug, I count how many calls are made to the function to make sure memoization is actually working
long calls = 0;

int numDigits(long n);
long countStones(long value, int iterations);

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    long stones[100];
    int numStones = 0;

    // read input
    while (!feof(f)) {
        fscanf(f, "%ld ", &stones[numStones]);
        numStones++;
    }

    // create hash table
    assert(hcreate(400000));

    // count the final number of stones for each initial stone in the input
    long sum = 0;
    for (int i = 0; i < numStones; i++) {
        sum += countStones(stones[i], 75);
    }

    // print results
    printf("result: %ld\n", sum);
    printf("number of calls: %ld\n", calls);

    // free memory
    hdestroy();
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

long countStones(long value, int iterations) {
    calls ++;
    long count;
    ENTRY entry;
    // the key is a string containing the value and the iterations
    entry.key = malloc(25);
    sprintf(entry.key, "%ld %d", value, iterations);
    // search the hash table to see if the function has been called with the same params
    ENTRY* result = hsearch(entry, FIND);
    if (result != NULL) {
        count = *(long*)result->data;
        return count;
    }
    // apply rules, recursively calling the function
    if (iterations == 0) {
        count = 1;
    }
    else if (value == 0) {
        count = countStones(1, iterations - 1);
    }
    else {
        int digits = numDigits(value);
        if (digits % 2 == 0) {
            long place = 1;
            for (int j = 0; j < digits/2; j++) {
                place *= 10;
            }
            long num1 = value / place;
            long num2 = value % place;
            count = countStones(num1, iterations-1) + countStones(num2, iterations-1);
        }
        else {
            count = countStones(value * 2024, iterations-1);
        }
    }
    // add the params and the result to the hash table before returning
    entry.data = malloc(sizeof(long));
    *(long*)entry.data = count;
    hsearch(entry, ENTER);

    return count;
}