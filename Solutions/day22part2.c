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

int getSecret(int n);
int sequenceToInt(int* seq);
void printSequence(int sequenceNum);

// sums up the cost for every possible sequence at once and finds the best result

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    // sequences contain 4 numbers each from -9 to 9 (that is 19 possible values total)
    // that means there are only 19**4 possible sequences (~130k)
    // that's managable
    int sequenceTotal[19 * 19 * 19 * 19] = {0};

    int secret;

    long sum = 0;

    // stores the latest buyer to have that sequence
    // to make sure sequences aren't double counted
    int seenSequence[19*19*19*19] = {0};

    int buyer = 1;
    int values[2000];
    int changes[2000];

    while (!feof(f)) {
        fscanf(f, "%d ", &secret);
        int previous = 0;
        for (int i = 0; i < 2000; i++) {
            secret = getSecret(secret);
            values[i] = (secret%10);
            changes[i] = (secret%10)-previous;
            previous = (secret%10);
        }
        for (int i = 1; i+3 < 2000; i++) {
            int sequenceNum = sequenceToInt(&changes[i]);
            if (seenSequence[sequenceNum] != buyer) {
                seenSequence[sequenceNum] = buyer;
                sequenceTotal[sequenceNum] += values[i+3];
            }
        }
        buyer ++;
    }
    int cost = 0;
    int sequence = 0;
    for (int i = 0; i < 19*19*19*19; i++) {
        assert(sequenceTotal[i] >= 0);
        if (sequenceTotal[i] > cost) {
            cost = sequenceTotal[i];
            sequence = i;
        }
    }
    printSequence(sequence);
    printf("%d\n", cost);
}

int getSecret(int n) {
    long result = n;
    result ^= (result*64);
    result %= 16777216;
    result ^= (result/32);
    result %= 16777216;
    result ^= (result*2048);
    result %= 16777216;
    return result;
}

// stores the sequence as a base 19 integer
int sequenceToInt(int* seq) {
    int result = 0;
    for (int i = 0; i < 4; i++) {
        result *= 19;
        result += seq[i] + 9;
    }
    return result;
}

void printSequence(int sequenceNum) {
    printf("%d, %d, %d, %d\n", sequenceNum/6859-9, (sequenceNum%6859)/361-9, (sequenceNum%361)/19-9, sequenceNum%19-9);
}