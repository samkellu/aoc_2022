#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	FILE* fp = fopen("day6.in", "r");
    char packet[5];
    packet[4] = '\0';
    int total = 0;

    while (1) {

        if (total < 4) {
            packet[total++] = fgetc(fp);
            continue;
        }

        for (int i = 0; i < 3; i++) {
            packet[i] = packet[i+1];
        }

        if ((packet[3] = fgetc(fp)) == '\0') {
            printf("No starting sequence detected...\n");
            break;
        }
        total++;
        // Manually checks all permutations
        int valid = (packet[0] != packet[1]) && (packet[0] != packet[2]) && (packet[0] != packet[3])
                     && (packet[1] != packet[2]) && (packet[1] != packet[3]) && (packet[2] != packet[3]);

        if (valid && total >= 3) {
            printf("%s %d\n", packet, total);
            break;
        }
    }
    fclose(fp);
    return 0;
}