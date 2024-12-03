#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assumes input does not end with an invalid mul instruction which is true for my input

int main() {
    FILE* f = fopen("input.txt", "r");

    char content[20000];
    fread(content, 1, 20000, f);

    int len = strlen(content);

    int sum = 0;
    for (int i = 0; i < len - 4; i++) {
        if (strncmp(content + i, "mul(", 4) == 0) {
            i += 4;
            int a = 0;
            int b = 0;
            while (content[i] >= '0' && content[i] <= '9') {
               a *= 10;
               a += content[i] - '0';
               i ++;
            }
            if (content[i] == ',') {
                i ++;
                while (content[i] >= '0' && content[i] <= '9') {
                    b *= 10;
                    b += content[i] - '0';
                    i ++;
                }
            }
            if (content[i] != ')') {
                a = 0;
            }
            sum += a * b;
        }
    }

    printf("%d\n", sum);
}