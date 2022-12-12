#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	FILE* fp = fopen("day5.in", "r");
	char buf[64];
    char** stacks;
    int mode = 0;

    int stack_count = 9;
    stacks = malloc(sizeof(char*) * stack_count);
    for (int i = 0; i < stack_count; i++) {
        stacks[i] = malloc(sizeof(char*));
        stacks[i][0] = '\0';
    }

    while (fgets(buf, 64, fp)) {

        int str_cursor = 1;
        switch (mode) {
            // Reads in configuration for the crate stacks
            case 0:

                if (buf[1] == '1') {
                    fgets(buf, 64, fp);
                    mode = 1;
                    continue;
                }

                int stack_cursor = 0;
                while (str_cursor <= strlen(buf)) {
                    if (buf[str_cursor] != ' ') {
                        int old_size = strlen(stacks[stack_cursor])+1;
                        stacks[stack_cursor] = realloc(stacks[stack_cursor], old_size+1);
                        stacks[stack_cursor][old_size-1] = buf[str_cursor];
                        stacks[stack_cursor][old_size] = '\0';
                    }
                    stack_cursor++;
                    str_cursor += 4;
                }
                break;

            // Processes movement commands for the crates
            case 1:

                int input[3];
                int cursor = 0;

                char* word = strtok(buf, " ");
                while (cursor < 3) {
                    input[cursor] = atoi(strtok(NULL, " "));
                    strtok(NULL, " ");
                    cursor++;
                }

                // Moves crates one by one from one stack to another
                for (int i = 0; i < input[0]; i++) {
                    stacks[input[2]-1] = realloc(stacks[input[2]-1], (size_t)strlen(stacks[input[2]-1])+2);
                    stacks[input[2]-1][strlen(stacks[input[2]-1])+1] = '\0';
                    for (int j = strlen(stacks[input[2]-1]); j > 0  ; j--) {
                        stacks[input[2]-1][j] = stacks[input[2]-1][j - 1];
                    }
                    stacks[input[2]-1][0] = stacks[input[1]-1][0];
                    
                    for (int j = 0; j < strlen(stacks[input[1]-1]) ; j++) {
                        stacks[input[1]-1][j] = stacks[input[1]-1][j + 1];
                    }
                }
                break;
        };
    }
    
    for (int i = 0; i < stack_count; i ++) {
        printf("%d: %c\n", i+1, stacks[i][0]);
        free(stacks[i]);
    }
    free(stacks);
    fclose(fp);
    return 0;
}