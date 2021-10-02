#ifndef nineteen_H_
#define nineteen_H_

#define MAX_SIZE 15


typedef struct LIST {
	struct LIST *prev, *next;
	char value[MAX_SIZE];
} LIST;

LIST* createList(char* value);
int pushFront(LIST** list, LIST* ne);
int pushBack(LIST** list, LIST* ne);
void deleteList(LIST** list);
int popFront(LIST** list, char* src);
int InsertBefore(LIST* q, LIST* ne);
int Sort(LIST* list);

#endif 
