#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
FILE* p, *p_new;
void get(int key) {
    int k;
    char value[256];
    while (!feof(p))
    {
        fscanf(p, "%d:%s", &k, value);
        if (k == key) {
            printf("%d,%s\n", key, value);
            return;
        }
    }
    printf("%d not found\n", key);
    return;
}

int put(int key, char* value) {
    fprintf(p, "%d:%s\n", key, value);
    return 1;
}

int del(int key) {
    int k;
    char value[256];
    while (feof(p))
    {
        fscanf(p, "%d:%s",&k, value);
        if (key == k) continue;
        fprintf(p_new, "%d:%s\n", k, value);
    }
    fclose(p_new);
    char* argv[3];
    argv[0] = "cp";
    argv[1] = "./kv.db.new";
    argv[2] = "./kv.db";
    execv("cp", argv);
    return 1;
}

int clear() {
    fclose(p);
    p = fopen("./kv.db", "w");
    fclose(p);
    return 1;
}

void all() {
    int k;
    char value[256];
    while (!feof(p))
    {
        fscanf(p, "%d:%s", &k, value);
        printf("%d,%s\n", k, value);
    }
}
int main(int argc, char *argv[])
{
    p = fopen("./kv.db", "a+");
    p_new = fopen("./kv.db.new", "w");
    if (argc != 2) {
        return 0;
    }
    char* now = strtok(argv[1], ",");
    if (!strcmp(now, "p")) {
        char* key = strtok(NULL, ",");
        int k = atoi(key);
        char* value = strtok(NULL, ",");
        put(k, value);
    } else if (!strcmp(now, "g")) {
        char* key = strtok(NULL, ",");
        int k = atoi(key);
        get(k);
    } else if (!strcmp(now, "d")) {
        char* key = strtok(NULL, ",");
        int k = atoi(key);
        del(k);
    } else if (!strcmp(now, "c")) {
        clear();
    } else if (!strcmp(now, "a")) {
        all();
    } else {
        fprintf(stderr, "command not found");
        exit(1);
    }
    fclose(p);   
    return 0;
}
