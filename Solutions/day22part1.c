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

int main() {
    FILE* f = fopen(FILE_NAME, "r");
    
    int secret;

    long sum = 0;

    while (!feof(f)) {
        fscanf(f, "%d ", &secret);
        printf("%d: ", secret);
        for (int i = 0; i < 2000; i++) {
            secret = getSecret(secret);
        }
        printf("%d\n", secret);
        sum += secret;
    }
    printf("%ld\n", sum);
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