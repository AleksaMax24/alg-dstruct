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

int pushFront(LIST** list, LIST* ne) {
  if (ne == NULL || ne->next != NULL)
      return 0;

  if (*list == NULL)
  {
    *list = ne;
    return 1;
  }

  LIST* head = *list;
  while (head->prev != NULL)
    head = head->prev;
  head->prev = ne;
  ne->next = head;
  return 1;
}

int pushBack(LIST** list, LIST* ne) {
  if (ne == NULL || ne->prev != NULL)
    return 0;

  if (*list == NULL)
  {
    *list = ne;
    return 1;
  }

  LIST* tail = *list;
  while (tail->next != NULL)
    tail = tail->next;
  tail->next = ne;
  ne->prev = tail;
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

int InsertBefore(LIST* ins, LIST* new0) {
  if (ins == NULL || new0 == NULL || new0->prev != NULL || new0->next != NULL)
    return 0;

  new0->prev = ins->prev;
  new0->next = ins;

  ins->prev = new0;
  if (new0->prev != NULL)
    new0->prev->next = new0;
  return 1;
}

int Sort(LIST* list)
{
  LIST* Cur = list;

  if (list == NULL)
    return 0;

  int flag = 1;
  do
  {
    while (Cur->prev != NULL)
      Cur = Cur->prev;
    flag = 0;
    while (Cur->next != NULL)
    {
      if (strcmp(Cur->value, Cur->next->value) == 1)
      {
        if (Cur->prev != NULL)
          Cur->prev->next = Cur->next;
        Cur->next->prev = Cur->prev;
        Cur->prev = Cur->next;

        if (Cur->next->next != NULL)
          Cur->next->next->prev = Cur;
        Cur->next = Cur->next->next;
        Cur->prev->next = Cur;
        flag = 1;
      }
      else
        Cur = Cur->next;
    }
  } while (flag);
  return 1;
}
