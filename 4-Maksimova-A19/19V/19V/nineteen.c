#include "nineteen.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

LIST* createList(char* value)
{
    LIST* tmp = (LIST*)malloc(sizeof(LIST));
    if (tmp == NULL)
    {
        printf("Allocation memory error!");
        return NULL;
    }

    tmp->next = tmp->prev = NULL;
    strcpy(tmp->value, value);

    return tmp;
}

int pushFront(LIST** list, LIST* newel) {
    if (newel == NULL || newel->next != NULL)
        return 0;

    if (*list == NULL)
    {
        *list = newel;
        return 1;
    }

    LIST* head = *list;
    while (head->prev != NULL)
        head = head->prev;
    head->prev = newel;
    newel->next = head;
    return 1;
}

int pushBack(LIST** list, LIST* newel) {
    if (newel == NULL || newel->prev != NULL)
        return 0;

    if (*list == NULL)
    {
        *list = newel;
        return 1;
    }

    LIST* tail = *list;
    while (tail->next != NULL)
        tail = tail->next;
    tail->next = newel;
    newel->prev = tail;
    return 1;
}

void deleteList(LIST** list)
{
    LIST* tmp = *list;
    LIST* next = NULL;

    if (tmp == NULL)
        return;

    while (tmp->prev != NULL)
        tmp = tmp->prev;

    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }

    (*list) = NULL;
}

int popFront(LIST** list, char* src) {
    LIST* tmp = *list;
    if (tmp == NULL)
    {
        src[0] = 0;
        return 0;
    }

    while (tmp->prev != NULL)
        tmp = tmp->prev;

    if (tmp == *list)
    {
        if (tmp->next != NULL)
            tmp->next->prev = NULL;
        *list = tmp->next;
    }
    else
        tmp->next->prev = NULL;
    strcpy(src, tmp->value);
    free(tmp);
    return 1;
}

int insertBefore(LIST* ins, LIST* newel) {
    if (ins == NULL || newel == NULL || newel->prev != NULL || newel->next != NULL)
        return 0;

    newel->prev = ins->prev;
    newel->next = ins;

    ins->prev = newel;
    if (newel->prev != NULL)
        newel->prev->next = newel;
    return 1;
}

int Sort(LIST* list)
{
    LIST* tmp = list;

    if (list == NULL)
        return 0;

    int flag = 1;
    do
    {
        while (tmp->prev != NULL)
            tmp = tmp->prev;
        flag = 0;
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->value, tmp->next->value) == 1)
            {
                if (tmp->prev != NULL)
                    tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                tmp->prev = tmp->next;

                if (tmp->next->next != NULL)
                    tmp->next->next->prev = tmp;
                tmp->next = tmp->next->next;
                tmp->prev->next = tmp;
                flag = 1;
            }
            else
                tmp = tmp->next;
        }
    } while (flag);
    return 1;
}
