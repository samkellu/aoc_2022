#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THRESHOLD 100000

struct directory {
    char* name;
    int size;
    struct directory* parent_dir;
    struct directory** sub_dir;
    int sub_size;
};

enum mode {
    LS,
    CD,
    DEF,
};

struct directory* init_directory(char* name) {
    struct directory* new_dir = malloc(sizeof(struct directory));
    new_dir->name = malloc(sizeof(char)*strlen(name)+1);
    memcpy(new_dir->name, name, strlen(name));
    new_dir->name[strlen(name)] = '\0';
    new_dir->size = 0;
    new_dir->sub_size = 0;
    new_dir->sub_dir = malloc(sizeof(struct directory*));
    return new_dir;
}

int main() {

	FILE* fp = fopen("day7.in", "r");
    char buf[64];
    struct directory* current_dir = init_directory("/");
    current_dir->parent_dir = NULL;
    struct directory* root = current_dir;

    int num_dirs = 1;
    struct directory** dirs = malloc(sizeof(struct directory*));
    dirs[0] = root;

    enum mode current_mode = DEF;

    while (fgets(buf, 64, fp)) {
        if (buf[0] == '$') {
            if (buf[2] == 'l'){
                current_mode = LS;
                continue;
            } else if (buf[2] == 'c'){
                current_mode = CD;
            }
        }

        char* sep = strtok(buf, " ");
        if (current_mode == LS) {
            if (strcmp(sep, "dir") == 0) {
                sep = strtok(NULL, " ");
                struct directory* new_dir = init_directory(sep);
                new_dir->parent_dir = current_dir;
                current_dir->sub_size++;
                current_dir->sub_dir = realloc(current_dir->sub_dir, current_dir->sub_size * sizeof(struct directory*));
                current_dir->sub_dir[current_dir->sub_size-1] = new_dir;
                dirs = realloc(dirs, sizeof(struct directory*) * ++num_dirs);
                dirs[num_dirs - 1] = new_dir;

            } else {
                int size = atoi(sep);
                current_dir->size += size;
                struct directory* cursor = current_dir->parent_dir;

                while (cursor != NULL) {
                    cursor->size += size;
                    cursor = cursor->parent_dir;
                }
            }

        } else if (current_mode == CD) {
            sep = strtok(NULL, " ");
            sep = strtok(NULL, " ");
            if (strcmp(sep, "..\n") == 0) {
                current_dir = current_dir->parent_dir;
                continue;
            } if (strcmp(sep, "/\n") == 0) {
                current_dir = root;
                continue;
            }

            for (int i = 0; i < current_dir->sub_size; i++) {
                if (strcmp(sep, current_dir->sub_dir[i]->name) == 0) {
                    current_dir = current_dir->sub_dir[i];
                    break;
                }
            }
        }
    }

    int total_size = 0;
    for (int i = 0; i < num_dirs; i++) {
        if (dirs[i]->size <= THRESHOLD) {
            total_size += dirs[i]->size;
        }
        free(dirs[i]->name);
        free(dirs[i]->sub_dir);
        free(dirs[i]);
    }
    free(dirs);

    printf("Total size of directories with at most 100000b size: %d\n", total_size);
    fclose(fp);
    return 0;
}