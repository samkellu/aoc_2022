#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct monkey {
    long int* items;
    int num_items;
    long int (*Operation)(long int a , long int b );
    int op_param;
    int test_div;
    int t;
    int f;
    int inspections;
};

long int mult(long int a, long int b) {
    return a*b;
}

long int add(long int a, long int b) {
    return a+b;
}

long int square(long int a, long int b) {
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
            long int* items = malloc(0);
            int num_items = 0;
            while ((tok = strtok(NULL, " ")) != NULL) {
                num_items++;
                items = realloc(items, sizeof(long int) * num_items);
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
    int mod = 1;
    for (int j = 0; j < num_monkey; j++) {
        mod *= monkeys[j].test_div;
    }

    fclose(fp);
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < num_monkey; j++) {
            for (int k = 0; k < monkeys[j].num_items; k++) {
                monkeys[j].inspections++;
                monkeys[j].items[k] = monkeys[j].Operation(monkeys[j].items[k], monkeys[j].op_param);
                monkeys[j].items[k] = monkeys[j].items[k]%mod;
                int throw = (int)(monkeys[j].items[k] % monkeys[j].test_div) == 0 ? monkeys[j].t : monkeys[j].f;

                monkeys[throw].num_items++;
                monkeys[throw].items = realloc(monkeys[throw].items, sizeof(long int) * monkeys[throw].num_items);
                monkeys[throw].items[monkeys[throw].num_items-1] = monkeys[j].items[k];
            }
            monkeys[j].num_items = 0;
            monkeys[j].items = realloc(monkeys[j].items, 0);
        }
    }

    int max = 0;
    int max2 = 1;

    for (int i = 0; i < num_monkey; i++) {
        printf("Monkey %d: %d\n", i, monkeys[i].inspections);
        if (monkeys[i].inspections >= monkeys[max].inspections) {
            max = i;
        }
        if (monkeys[i].inspections >= monkeys[max2].inspections && monkeys[i].inspections <= monkeys[max].inspections && i != max){
            max2 = i;

        } 
    }
    printf("Monkey Business: %lld\n", (long long int)monkeys[max].inspections * (long long int) monkeys[max2].inspections);

    for (int i = 0; i < num_monkey; i++) {
        free(monkeys[i].items);
    }
    free(monkeys);
    return 1;
}