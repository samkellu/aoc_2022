#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* fp = fopen("day3.in", "r");
    char buf1[64];
    char buf2[64];
    char buf3[64];
    int total = 0;

    while(fgets(buf1, 64, fp)) {
        fgets(buf2, 64, fp);
        fgets(buf3, 64, fp);

        for (int i = 0; i < strlen(buf1); i++) {
            for (int j = 0; j < strlen(buf2); j++) {
                if (buf1[i] == buf2[j]) {
                    for (int k = 0; k < strlen(buf3); k++) {
                        if (buf2[j] == buf3[k]) {
                            total += ((int) buf2[j] >= 97 && (int) buf2[j] <= 122) ? (int) buf2[j] - 96 : 0;
                            total += ((int) buf2[j] >= 65 && (int) buf2[j] <= 90) ? (int) buf2[j] - 38 : 0;
                            goto NEXT;
                        }
                    }
                }
            }
        }
        NEXT:
    }
    printf("%d\n", total);
    return 0;
}