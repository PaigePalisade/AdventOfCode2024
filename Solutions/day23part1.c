#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEST

#ifdef TEST
#define FILE_NAME "test.txt"
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#endif

// creats a list of all t computers and their connections
// goes through the list checking each possible pair of connections to see if they are connected

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // connectionMatrix[i][j] = 1 if the computers represented by i and j are connected
    int connectionMatrix[26*26][26*26] = {0};

    // list of connections to computers starting with t
    int tLists[26][26*26] = {0};
    int tListLengths[26] = {0};

    while (!feof(f)) {
        char label1[2];
        char label2[2];
        fscanf(f, "%2c-%2c ", &label1, &label2);
        int index1 = 26 * (label1[0]-'a') + (label1[1]-'a');
        int index2 = 26 * (label2[0]-'a') + (label2[1]-'a');
        connectionMatrix[index1][index2] = 1;
        connectionMatrix[index2][index1] = 1;
        if (label1[0] == 't') {
            tLists[index1%26][tListLengths[index1%26]++] = index2;
        }
        if (label2[0] == 't') {
            tLists[index2%26][tListLengths[index2%26]++] = index1;
        }
    }
    // count (and print) all t computers and networks of three containing them
    int count = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < tListLengths[i]; j++) {
            for (int k = j+1; k < tListLengths[i]; k++) {
                int index1 = tLists[i][j];
                int index2 = tLists[i][k];
                // prevent double count if there is a t computer in the list
                if (index1/26 == 't' - 'a' && index1%26 < i) {
                    continue;
                } 
                if (index2/26 == 't' - 'a' && index2%26 < i) {
                    continue;
                } 
                if (connectionMatrix[index1][index2]) {
                    printf("t%c: ", i + 'a');
                    printf("%c%c, ", index1/26+'a', index1%26 + 'a');
                    printf("%c%c\n", index2/26+'a', index2%26 + 'a');

                    count ++;
                }

            }
        }
    }
    printf("%d\n", count);


}