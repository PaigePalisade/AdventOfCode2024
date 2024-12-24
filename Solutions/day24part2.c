#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT

#ifdef TEST
#define FILE_NAME "test.txt"
#define NUM_INPUTS 12
#endif

#ifdef INPUT
#define FILE_NAME "input.txt"
#define NUM_INPUTS 90
#endif

// adds a classification to each gate
// each classification has other classifications as its expected inputs
// if those inputs do not match, those inputs have the wrong outputs
// print a sorted list of all of the wrong outputs
// it is not necessary to actually make the swaps

typedef struct {
    int inputA;
    int inputB;
    int operation;
    int state;
    int classification;
} Wire;

// gates
enum {
    AND,
    OR,
    XOR,
    NONE
};

// classifications
enum {
    // XOR gates whose inputs are x00, y00 (part of half adder)
    XOR1,
    // XOR gate whose inputs are other inputs to the system
    XOR2,
    // other XOR gates
    XOR3,
    // AND gate whose inputs are x00, y00 (part of half adder)
    AND1,
    // AND gate whose inputs are other inputs to the system
    AND2,
    // other AND gates
    AND3,
    // any OR gate
    OR1,
    // input
    INPUT1
};

int getValue(Wire w);
int labelToIndex(char label[3]);
void printLabel(int index);
void printWire(int index);
void indexToLabel(int index, char label[4]);
int containsLabel(char list[8][4], int size, char label[4]);
void addProblem(int index);
int max(int a, int b);
int comp(const void *a, const void *b);

// wires are stored here for fast lookups
Wire wireTable[36*36*36] = {0};

// list of problem labels
char problemLabels[8][4] = {0};
int numProblems = 0;

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    // outputs are stored here as well for easy looping
    int outputWires[50];
    int numOutputs = 0;

    for (int i = 0; i < NUM_INPUTS; i++) {
        char label[3];
        int state = 0;
        fscanf(f, "%3c: %d ", label, &state);
        int index = labelToIndex(label);
        wireTable[index] = (Wire){-1, -1, NONE, state, INPUT1};
    }

    int wireList[300];
    int numWires = 0;

    // go through input
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
        // classify gate by inputs
        if (w.inputA == labelToIndex("x00") || w.inputB == labelToIndex("x00")) {
            if (w.operation == XOR) {
                w.classification = XOR1;
            }
            else if (w.operation == AND) {
                w.classification = AND1;
            }
            else {
                assert(0);
            }
        }
        else if (wireTable[w.inputA].classification == INPUT1) {
            if (w.operation == XOR) {
                w.classification = XOR2;
            }
            else if (w.operation == AND) {
                w.classification = AND2;
            }
            else {
                assert(0);
            }
        }
        else {
            if (w.operation == XOR) {
                w.classification = XOR3;
            }
            else if (w.operation == AND) {
                w.classification = AND3;
            }
            else if (w.operation == OR) {
                w.classification = OR1;
            }
            else {
                assert(0);
            }
        }
        wireTable[index] = w;
        wireList[numWires++] = index;
        // output wire
        if (label[0] == 'z') {
            int zIndex = atoi(&label[1]);
            numOutputs = max(numOutputs, zIndex+1);
            outputWires[zIndex] = index;
        }
    }
    
    // check output wires
    for (int i = 0; i < numOutputs; i++) {
        Wire w = wireTable[outputWires[i]];
        if (i == 0 && w.classification == XOR1) {
            continue;
        }
        if (i == numOutputs-1 && w.classification == OR1) {
            continue;
        }
        if (w.classification == XOR3) {
            continue;
        }
        addProblem(outputWires[i]);
    }
    // check other wires
    for (int i = 0; i < numWires; i++) {
        Wire w = wireTable[wireList[i]];
        Wire a = wireTable[w.inputA];
        Wire b = wireTable[w.inputB];
        // INPUTS should be XOR2 and OR1/AND1
        if (w.classification == XOR3 || w.classification == AND3) {
            if (a.classification != XOR2 && a.classification != OR1 && a.classification != AND1) {
                addProblem(w.inputA);
            }
            if (b.classification != XOR2 && b.classification != OR1 && b.classification != AND1) {
                addProblem(w.inputB);
            }
        }
        // INPUTS should be AND2 and AND3
        if (w.classification == OR1) {
            if (a.classification != AND2 && a.classification != AND3) {
                addProblem(w.inputA);
            }
            if (b.classification != AND2 && b.classification != AND3) {
                addProblem(w.inputB);
            }
        }
    }
    // sort and print problems
    qsort(problemLabels, numProblems, sizeof(char)*4, comp);
    for (int i = 0; i < numProblems; i++) {
        printf("%s", problemLabels[i]);
        if (i != numProblems-1) {
            printf(",");
        }
    }
    printf("\n");
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

// prints a wire in a form matching input.txt
void printWire(int index) {
    Wire w = wireTable[index];
    printLabel(w.inputA);
    if (w.operation == OR) {
        printf(" OR ");
    }
    if (w.operation == AND) {
        printf(" AND ");
    }
    if (w.operation == XOR) {
        printf(" XOR ");
    }
    printLabel(w.inputB);
    printf(" -> ");
    printLabel(index);
    printf("\n");
}

// gets a label from the input
void indexToLabel(int index, char label[4]) {
    label[0] = index/1296;
    label[1] = (index/36)%36;
    label[2] = index%36;
    for (int i = 0; i < 3; i++) {
        if (label[i] < 26) {
            label[i] += 'a';
        }
        else if (label[i] >= 26) {
            label[i] -= 26;
            label[i] += '0';
        }
    }
    label[3] = '\0';
}

// adds a problem to the problemList if it isn't in there already
// prints the problem just for fun
void addProblem(int index) {
    char label[4];
    indexToLabel(index, label);
    if (!containsLabel(problemLabels, numProblems, label)) {
        printWire(index);
        strcpy(problemLabels[numProblems++], label);
    }
}

// checks if list contains label
int containsLabel(char list[8][4], int size, char label[4]) {
    for (int i = 0; i < size; i++) {
        if (strncmp(label, list[i], 3) == 0) {
            return 1;
        }
    }
    return 0;
}

// prints a label from the index
void printLabel(int index) {
    char label[4];
    indexToLabel(index, label);
    printf("%s", label);
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int comp(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b);
}