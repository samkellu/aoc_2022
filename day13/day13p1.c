#include <stdio.h>
#include <stdlib.h>

int main() {
    char buf1[256];
    char buf2[256];
    FILE* fp = fopen("day13.in", "r");


    int total = 0;
    int ind = 0;
    while (fgets(buf1, 256, fp)) {
        fgets(buf2, 256, fp);

        int curs1, curs2, nest1, nest2;
        curs1 = curs2 = nest1 = nest2 = 0;

        while (1) {

            while (buf1[curs1] < 48 || buf1[curs1] > 57) {
                if (buf1[curs1] == '[') {nest1++;}
                if (buf1[curs1] == ']') {nest1--;}
                curs1++;
            }
            while (buf2[curs2] < 48 || buf2[curs2] > 57) {
                if (buf2[curs2] == '[') {nest2++;}
                if (buf2[curs2] == ']') {nest2--;}
                curs2++;
            }

            int start1 = curs1;
            int start2 = curs2;
            char v1[16];
            char v2[16];

            while (buf1[curs1] != ',') {
                v1[curs1-start1] = buf1[curs1];
                curs1++;
            }
            v1[curs1-start1] = '\0';
            printf("%d\n", atoi(v1));

            while (buf2[curs2] != ',') {
                v2[curs2-start2] = buf2[curs2];
                curs2++;
            }
            v2[curs2-start2] = '\0';
            printf("%d\n", atoi(v2));
            return 1;

            // if (buf1[curs1] != buf2[curs2]) {
            //     if ((int)buf1[curs1]) > atoi(buf2[curs2])) {
            //         printf("Left larger, correct order. %d\n", ind);
            //         break;
            //     } else if (atoi(buf1[curs1]) < atoi(buf2[curs2])) {
            //         printf("Right larger, incorrect order.\n");
            //         break;
            //     }
            // }   
        }
        ind++;
    }
    printf("%d\n", total);

    fclose(fp);
}