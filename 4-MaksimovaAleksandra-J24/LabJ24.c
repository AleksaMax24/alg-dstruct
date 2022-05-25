#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define size 1000

typedef struct {
    int key;
    char* str;
} hash_t;

hash_t* table;
char* buck;


void create() {
    table = (hash_t*)malloc(size * sizeof(hash_t));
    if (table == NULL) {
        return;
    }
    buck = (char*)malloc(size * sizeof(char));
    if (buck == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        table[i].key = -1;
        table[i].str = NULL;
        buck[i] = 0;
    }
}


int find(int key) {
    int x = key % size;
    for (int i = 1; i <= size; i++) {
        if (table[x].key != -1) {
            if ((table[x].key == key) && !buck[x]) {
                return 1;
            }
            else {
                return 0;
            }
        }

    }
    return 0;
}

void add(int key, char* str) {
    if (find(key))
        return;
    int x = key % size;
    for (int i = 1; i <= size; i++) {
        if ((table[x].key == -1) || buck[x]) {
            table[x].key = key;
            table[x].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
            if (table[x].str == NULL)
                return;
            strcpy(table[x].str, str);
            table[x].str[strlen(str)] = '\0';
            buck[x] = 0;
            return;
        }
    }
}

void del(int key) {
    if (!find(key)) {
        return;
    }
    int x = key % size;
    for (int i = 1; i <= size; i++) {
        if (table[x].key != -1) {
            if (table[x].key == key) {
                buck[x] = 1;
            }
            else {
                return;
            }
        }
    }
}

void destroy() {
    if (table == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        free(table[i].str);
    }
    free(table);
    table = NULL;
    free(buck);
}

int main() {
    create();
    char command;
    int key;
    while (scanf("%c", &command) >= 1) {
        scanf("%d", &key);
        switch (command) {
        case 'a':
            add(key, "");
            break;
        case 'r':
            del(key);
            break;
        case 'f':
            if (find(key)) {
                puts("yes");
            }
            else {
                puts("no");
            }
            break;
        }
    }
    destroy();
    return 0;
}
