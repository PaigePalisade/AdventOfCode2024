#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define NUM_INPUTS 10
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define NUM_INPUTS 90
#endif

// goes through the wires backwards, starting at the outputs and going to the inputs

typedef struct {
    int inputA;
    int inputB;
    int operation;
    int state;
} Wire;

enum {
    AND,
    OR,
    XOR,
    NONE
};

int getValue(Wire w);
int labelToIndex(char label[3]);
int max(int a, int b);

// wires are stored here for fast lookups
// index is based on where that wire outputs
Wire wireTable[36*36*36];

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // outputs are stored here as well for easy looping
    Wire outputWires[50];
    int numOutputs = 0;

    // get the inputs to the system
    // input wires have their state already set, the inputs and operation are irrelevant
    for (int i = 0; i < NUM_INPUTS; i++) {
        char label[3];
        int state = 0;
        fscanf(f, "%3c: %d ", label, &state);
        int index = labelToIndex(label);
        wireTable[index] = (Wire){-1, -1, NONE, state};
    }

    // get the other wires
    while (!feof(f)) {
        Wire w;
        char label[4];
        char inLabelA[3];
        char inLabelB[3];
        char operationLabel[4];
        fscanf(f, "%s %s %3c -> %3c ", inLabelA, operationLabel, inLabelB, label);
        if (operationLabel[0] == 'A') {
            w.operation = AND;
        }
        else if (operationLabel[0] == 'O') {
            w.operation = OR;
        }
        else if (operationLabel[0] == 'X') {
            w.operation = XOR;
        }
        else {
            assert(0);
        }
        int index = labelToIndex(label);
        w.inputA = labelToIndex(inLabelA);
        w.inputB = labelToIndex(inLabelB);
        w.state = -1;
        wireTable[index] = w;
        // output wire
        if (label[0] == 'z') {
            int zIndex = atoi(&label[1]);
            numOutputs = max(numOutputs, zIndex+1);
            outputWires[zIndex] = w;
        }
    }

    // get the value of the outputs and add them to the binary value
    long value = 0;
    for (int i = numOutputs-1; i >= 0; i--) {
        value *= 2;
        value += getValue(outputWires[i]);
    }

    printf("%lb: %ld\n", value, value);
}

// get the state of a particular wire
int getValue(Wire w) {
    if (w.state != -1) {
        return w.state;
    }
    if (w.operation == AND) {
        return getValue(wireTable[w.inputA]) && getValue(wireTable[w.inputB]);
    }
    if (w.operation == OR) {
        return getValue(wireTable[w.inputA]) || getValue(wireTable[w.inputB]);
    }
    if (w.operation == XOR) {
        return getValue(wireTable[w.inputA]) != getValue(wireTable[w.inputB]);
    }
    assert(0);
}

// converts a 3 character label to a base 36 number
int labelToIndex(char* label) {
    int result = 0;
    for (int i = 0; i < 3; i++) {
        result *= 36;
        if (label[i] >= 'a' && label[i] <= 'z') {
            result += label[i] - 'a';
        }
        if (label[i] >= '0' && label[i] <= '9') {
            result += label[i] - '0' + 26;
        }
    }
    assert(result >= 0 && result < 36*36*36);
    return result;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}