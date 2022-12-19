#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct monkey {
    int* items;
    int num_items;
    int (*Operation)(int a , int b );
    int op_param;
    int test_div;
    int t;
    int f;
    int inspections;
};

int mult(int a, int b) {
    return a*b;
}

int add(int a, int b) {
    return a+b;
}

int square(int a, int b) {
    return a*a;
}

int main() {

    FILE* fp = fopen("day11.in", "r");
    char buf[64];

    struct monkey* monkeys = malloc(0);
    int num_monkey = 0;

    while (fgets(buf, 64, fp)) {
        char* tok = strtok(buf, " ");

        if (strcmp(tok, "Monkey") == 0) {
            num_monkey++;
            monkeys = realloc(monkeys, sizeof(struct monkey) * num_monkey);
            struct monkey new_monkey;
            new_monkey.inspections = 0;
            monkeys[num_monkey-1] = new_monkey;

        } else if (strcmp(tok, "Starting") == 0) {

            strtok(NULL," ");
            int* items = malloc(0);
            int num_items = 0;
            while ((tok = strtok(NULL, " ")) != NULL) {
                num_items++;
                items = realloc(items, sizeof(int) * num_items);
                items[num_items-1] = atoi(tok);
            }
            monkeys[num_monkey-1].items = items;
            monkeys[num_monkey-1].num_items = num_items;

        } else if (strcmp(tok, "Operation:") == 0) {

            tok = strtok(NULL," ");
            tok = strtok(NULL," ");
            tok = strtok(NULL," ");
            tok = strtok(NULL," ");
            monkeys[num_monkey-1].Operation = (strcmp(tok, "*") == 0) ? &mult : &add;
            tok = strtok(NULL," ");
            if (strcmp(tok, "old\n") == 0) {
                monkeys[num_monkey-1].Operation = &square;
                continue;
            }
            monkeys[num_monkey-1].op_param = atoi(tok);

        } else if (strcmp(tok, "Test:") == 0) {
            tok = strtok(NULL, " ");
            tok = strtok(NULL, " ");
            tok = strtok(NULL, " ");
            monkeys[num_monkey-1].test_div = atoi(tok);
        
        } else if (strcmp(tok, "If") == 0) {
            char* op = strtok(NULL, " ");
            tok = strtok(NULL, " ");
            tok = strtok(NULL, " ");
            tok = strtok(NULL, " ");
            tok = strtok(NULL, " ");

            if (strcmp(op, "true:") == 0) {
                monkeys[num_monkey-1].t = atoi(tok);
            } else if (strcmp(op, "false:") == 0) {
                monkeys[num_monkey-1].f = atoi(tok);
            }
        }
    }

    fclose(fp);
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < num_monkey; j++) {
            for (int k = 0; k < monkeys[j].num_items; k++) {
                monkeys[j].inspections++;
                monkeys[j].items[k] = monkeys[j].Operation(monkeys[j].items[k], monkeys[j].op_param);
                monkeys[j].items[k] = (int) monkeys[j].items[k]/3;
                int throw = (int)(monkeys[j].items[k] % monkeys[j].test_div) == 0 ? monkeys[j].t : monkeys[j].f;

                monkeys[throw].num_items++;
                monkeys[throw].items = realloc(monkeys[throw].items, sizeof(int) * monkeys[throw].num_items);
                monkeys[throw].items[monkeys[throw].num_items-1] = monkeys[j].items[k];

            }
            monkeys[j].num_items = 0;
        }
    }

    int max = 0;
    int max2 = 1;

    for (int i = 0; i < num_monkey; i++) {
        printf("Monkey %d: %d\n", i, monkeys[i].inspections);
        if (monkeys[i].inspections >= monkeys[max].inspections) {
            max2 = max;
            max = i;
        }
    }

    printf("Monkey Business: %d\n", monkeys[max].inspections * monkeys[max2].inspections);

    for (int i = 0; i < num_monkey; i++) {
        free(monkeys[i].items);
    }
    free(monkeys);
    return 1;
}