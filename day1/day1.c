#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* buf = malloc(sizeof(char) * 16);
    FILE* fp = fopen("day1.in", "r");

    int top[3] = {0,0,0};
    int current = 0;

    while (fgets(buf, 16, fp)) {

        if (strcmp(buf, "\n") == 0) {
            for (int i = 0; i < 3; i++) {
                if (current > top[i]) {

                    for (int j = 2; j > i; j--) {
                        top[j] = top[j-1];
                    }
                    top[i] = current;
                    break;
                }
            }
            current = 0;
        }
        current += atoi(buf);
    }

    int total = top[0] + top[1] + top[2];

    printf("1: %d\n", top[0]);
    printf("2: %d\n", top[1]);
    printf("3: %d\n\n", top[2]);

    printf("Total: %d\n", total);

    free(buf);
    fclose(fp);
}