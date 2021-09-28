#ifndef nineteen_H_
#define nineteen_H_


#define MAX_SIZE 15
#define LIST_SIZE 6

typedef struct DATA {
	char value[MAX_SIZE];
} DATA;

typedef struct NODE {
	DATA value;
	struct NODE* next;
	struct NODE* prev;
} NODE;

typedef struct LIST {
	NODE* head;
	NODE* tail;
} LIST;

LIST* createList();
void deleteList(LIST** list);
void pushFront(LIST* list, char* value);
DATA popFront(LIST* list);
void pushBack(LIST* list, char* value);
void InsertBefore(LIST* list, NODE* elm, char* value);
int Sort(LIST** List);

#endif 
