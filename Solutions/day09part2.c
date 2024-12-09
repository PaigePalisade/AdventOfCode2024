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

// doubly linked list for faster insertions and removals

typedef struct FileNode FileNode;

struct FileNode {
    int id;
    int size;
    int freeSpace;
    FileNode* next;
    FileNode* prev;
};

int main() {
    FILE* f = fopen(FILE_NAME, "r");

    char str[30000];

    fscanf(f, "%s ", &str);

    // read input
    int len = strlen(str);
    FileNode start = {0, str[0] - '0', str[1] - '0'};
    FileNode* end = &start;
    for (int i = 2; i < len; i+=2) {
        FileNode* newEnd = calloc(1, sizeof(FileNode));
        newEnd->id = i/2;
        newEnd->size = str[i] - '0';
        if (i+1 < len) {
            newEnd->freeSpace = str[i+1] - '0';
        }
        end->next = newEnd;
        newEnd->prev = end;
        end = newEnd;
    }

    // move files to free space
    FileNode* n1 = end;
    while (n1 != NULL) {
        FileNode* prev = n1->prev;
        // linked list for loop
        for (FileNode* n2 = &start; n2 != n1 && n2 != NULL; n2 = n2->next) {
            if (n2->freeSpace >= n1->size) {
                // delete n1 from list
                if (n1->prev != NULL) {
                    n1->prev->next = n1->next;
                    n1->prev->freeSpace += n1->size + n1->freeSpace;
                }
                if (n1->next != NULL) {
                    n1->next->prev = n1->prev;
                }
                // insert it to the list after n2
                if (n2->next != NULL) {
                    n2->next->prev = n1;
                    n1->next = n2->next;
                }
                n1->freeSpace = n2->freeSpace - n1->size;
                n2->freeSpace = 0;
                n2->next = n1;
                n1->prev = n2;
                break;
            }
        }
        n1 = prev;
    }

    // calculate sum
    long sum = 0;
    int position = 0;
    for (FileNode* n = &start; n != NULL; n = n->next) {
        for (int i = 0; i < n->size; i++) {
            sum += n->id * position;
            position ++;
        }
        for (int i = 0; i < n->freeSpace; i++) {
            position ++;
        }
    }

    printf("%ld\n", sum);

    // free linked list
    FileNode* n = start.next;
    while (n != NULL) {
        FileNode* toFree = n;
        n = n->next;
        free(toFree);
    }
}