#ifndef nine_H_
#define nine_H_

typedef struct LIST {
	struct LIST* prev, * next;
	char* value;
} LIST;

LIST* createList(char* value);
int pushFront(LIST** list, LIST* newel);
int pushBack(LIST** list, LIST* newel);
void deleteList(LIST** list);
int popFront(LIST** list, char* src);
int insertBefore(LIST* ins, LIST* newel);
int Sort(LIST* list);

#endif 
