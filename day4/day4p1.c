#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE* fp = fopen("day4.in", "r");
	char buf[32];
	int elves[4];
	int total = 0;

	while (fgets(buf, 32, fp)) {

		elves[0] = atoi(strtok(buf, "-"));
		elves[1] = atoi(strtok(NULL, ","));

		elves[2] = atoi(strtok(NULL, "-"));
		elves[3] = atoi(strtok(NULL, "\n"));

		if (elves[0] == elves[2] && elves[1] == elves[3]) {
			total++;
			continue;
		}

		total += (elves[0] <= elves[2] && elves[1] >= elves[3]) ? 1 : 0;
		total += (elves[2] <= elves[0] && elves[3] >= elves[1]) ? 1 : 0;
	}

	printf("%d\n", total);
	fclose(fp);
	return 0;
}

