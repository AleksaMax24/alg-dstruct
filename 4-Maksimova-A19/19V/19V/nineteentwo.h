#ifndef nineteentwo_H_
#define nineteentwo_H_


typedef struct LIST{
	struct LIST* prev, * next;
	char *value;
} LIST;

LIST* createList(char* value);
int pushFront(LIST** list, LIST* ne);
int pushBack(LIST** list, LIST* ne);
void deleteList(LIST** list);
int popFront(LIST** list, char* src);
int insertBefore(LIST* q, LIST* ne);
int Sort(LIST* list);

#endif 