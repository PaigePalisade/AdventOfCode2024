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

int checkAllCombinations(int arr[], int size, int combination[]);
int checkAllCombinationsOfR(int arr[], int n, int r, int index, int data[], int i);
int checkCombination(int* combination, int size);
int comp(const void *a, const void *b);

int connectionMatrix[26*26][26*26] = {0};

// creates a list of every computer and its connections
// checks every combination of those connections to see if it is a clique
// prints the clique of the greatest length

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // list of computers and their connections
    int connectionLists[26*26][26*26];
    int connectionListLenghts[26*26] = {0};

    // read input
    while (!feof(f)) {
        char label1[2];
        char label2[2];
        fscanf(f, "%2c-%2c ", &label1, &label2);
        int index1 = 26 * (label1[0]-'a') + (label1[1]-'a');
        int index2 = 26 * (label2[0]-'a') + (label2[1]-'a');
        connectionMatrix[index1][index2] = 1;
        connectionMatrix[index2][index1] = 1;
        connectionLists[index1][connectionListLenghts[index1]++] = index2;
        connectionLists[index2][connectionListLenghts[index2]++] = index1;
    }

    // get all cliques and mark the current best one
    // all computers in the network are connected to exactly 13 others, so the max clique size is 14
    int cliques[26*26][14] = {0};
    int cliqueLengths[26*26] = {0};
    int bestCliqueLength = 0;
    int bestCliqueIndex = 0;
    for (int i = 0; i < 26*26; i++) {
        if (connectionListLenghts[i] != 0) {
            cliqueLengths[i] = checkAllCombinations(connectionLists[i], connectionListLenghts[i], cliques[i]);
            cliques[i][cliqueLengths[i]++] = i;
            if (cliqueLengths[i] > bestCliqueLength) {
                bestCliqueLength = cliqueLengths[i];
                bestCliqueIndex = i;
            }
        }
    }

    // sort the clique
    qsort(cliques[bestCliqueIndex], bestCliqueLength, sizeof(int), comp);

    // print the clique
    for (int i = 0; i < bestCliqueLength; i++) {
        printf("%c%c", (cliques[bestCliqueIndex][i]/26) +'a', (cliques[bestCliqueIndex][i]%26) +'a');
        if (i != bestCliqueLength-1) {
            printf(",");
        }
    }
    printf("\n");
}

// checks all combinations of arr for cliques
// returns the size of the clique
// combination is the clique that is found
int checkAllCombinations(int arr[], int size, int combination[]) {
    for (int i = size; i >= 1; i--) {
        if (checkAllCombinationsOfR(arr, size, i, 0, combination, 0)) {
            return i;
        }
    }
    return 0;
}

// modified from: https://www.geeksforgeeks.org/print-subsets-given-size-set/
// checks all subsets of size r of arr for cliques
int checkAllCombinationsOfR(int arr[], int n, int r, int index, int data[], int i) {
    // Current combination is ready, check it
    if (index == r) {
        if (checkCombination(data, r)) {
            return 1;
        }
        return 0;
    }
 
    // When no more elements are there to put in data[]
    if (i >= n) {
        return 0;
    }
 
    // current is included, put next at next location
    data[index] = arr[i];
    if (checkAllCombinationsOfR(arr, n, r, index + 1, data, i + 1)) {
        return 1;
    }
 
    // current is excluded, replace it with next
    // (Note that i+1 is passed, but index is not
    // changed)
    if (checkAllCombinationsOfR(arr, n, r, index, data, i + 1)) {
        return 1;
    }
    return 0;
}

// checks if a combination is a clique
int checkCombination(int* combination, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (!connectionMatrix[combination[i]][combination[j]]) {
                return 0;
            }
        }
    }
    return 1;
}

// comparison function for qsort
int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}