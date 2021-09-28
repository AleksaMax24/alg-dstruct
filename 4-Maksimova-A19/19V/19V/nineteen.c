#include "nineteen.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)


LIST* createList() {
    LIST* tmp = (LIST*)malloc(sizeof(LIST));
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void deleteList(LIST** list) {
    NODE* tmp = (*list)->head;
    NODE* next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(LIST* list, char* value) {
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    if (tmp == NULL)
        return;
    strcpy(tmp->value.value, value);
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head)
        list->head->prev = tmp;
    list->head = tmp;
    if (list->tail == NULL)
        list->tail = list->head;
}

DATA popFront(LIST* list) {
    NODE* prev;
    DATA tmp = { 0 };
    if (list->head == NULL)
        return tmp;
    prev = list->head;
    list->head = list->head->next;
    if (list->head)
        list->head->prev = NULL;
    else
        list->tail = NULL;
    tmp = prev->value;
    free(prev);
    return tmp;
}

void pushBack(LIST* list, char* value) {
    NODE* newEl = (NODE*)malloc(sizeof(NODE));
    NODE* tmp1 = NULL;

    if (newEl == NULL) {
        exit(3);
    }
    if (list->head == NULL) {
        pushFront(list, value);
    }
    else {
        tmp1 = list->tail;

        newEl->prev = tmp1;
        newEl->next = NULL;
        strcpy(newEl->value.value, value);

        tmp1->next = newEl;
        list->tail = newEl;
    }
}

void InsertBefore(LIST* list, NODE* q, char* value) {
    NODE* ins = NULL;
    if (q == NULL) {
        return;
    }
    if (!q->prev) {
        pushFront(list, value);
        return;
    }
    ins = (NODE*)malloc(sizeof(NODE));
    if (ins == NULL) {
        return;
    }
    strcpy(ins->value.value, value);
    ins->prev = q->prev;
    ins->next = q;

    q->prev = ins;

    ins->prev->next = ins;
}

int Sort(LIST** List) {
    if ((*List)->head == NULL) {
        return 0;
    }
    LIST* firstl = createList();
    NODE* secondl = NULL;
    NODE* unsort = NULL;
    DATA tmp = popFront(*List);
    pushFront(firstl, tmp.value);

    unsort = (*List)->head;
    while (unsort != NULL) {
        secondl = firstl->tail;
        int result = strcmp(unsort->value.value, secondl->value.value);

        while (secondl != NULL && secondl->prev != NULL && result < 0) {
            secondl = secondl->prev;
            result = strcmp(unsort->value.value, secondl->value.value);
        }
        if (result < 0)
            InsertBefore(firstl, secondl, unsort->value.value);
        else if (secondl->next != NULL)
            InsertBefore(firstl, secondl->next, unsort->value.value);
        else
            pushBack(firstl, unsort->value.value);
        unsort = unsort->next;
    }
    free(*List);
    *List = firstl;
    return 1;
}

