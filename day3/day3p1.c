#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* fp = fopen("day3.in", "r");
    char buf[64];
    int total = 0;

    while (fgets(buf, 64, fp)) {

        int mid = (strlen(buf))/2;
        
        int valid = 0;
        for (int i = 0; i < mid; i++) {
            for (int j = mid; j < strlen(buf); j++) {
                if (buf[i] == buf[j]) {

                    if ((int) buf[i] >= 97 && (int) buf[i] <= 122) {
                        total += (int) buf[i] - 96;

                    } else if ((int) buf[i] >= 65 && (int) buf[i] <= 90) {
                        total += (int) buf[i] - 38;
                    }
                    valid = 1;
                    break;
                }
            }
            if (valid) {
                break;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}