#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	FILE* fp = fopen("day6.in", "r");
    char packet[15];
    packet[14] = '\0';
    int total = 0;

    while (1) {

        if (total < 14) {
            packet[total++] = fgetc(fp);
            continue;
        }

        for (int i = 0; i < 13; i++) {
            packet[i] = packet[i+1];
        }
        
        if ((packet[13] = fgetc(fp)) == '\0') {
            printf("No starting sequence detected...\n");
            break;
        }
        total++;
        int valid = 1;
        
        for (int i = 0; i < 14; i++) {
            for (int j = i + 1; j < 14; j++) {
                if (packet[i] == packet[j]) {
                    valid = 0;
                    goto LABEL;
                }
            }
        }
        LABEL:
        if (valid && total >= 13) {
            printf("%s %d\n", packet, total);
            break;
        }
    }
    fclose(fp);
    return 0;
}