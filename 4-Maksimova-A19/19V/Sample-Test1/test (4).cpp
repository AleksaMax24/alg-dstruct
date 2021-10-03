#include "pch.h"
extern "C"
{
#include "nineteen.h"
#define MAX_SIZE 15
}


LIST node[6];

void set(void)
{
  for (int i = 0; i < 6; i++)
    node[i].value[0] = node[i].value[1] = i + '0',
    node[i].value[2] = 0, node[i].next = node[i].prev = nullptr;

}

TEST(pushFront, EmptyList1_NewElement00)
{
  set();
  LIST* list = NULL;

  pushFront(&list, &node[0]);
  EXPECT_EQ(list, &node[0]);
  EXPECT_EQ(strcmp(list->value, "00"), 0);
}

TEST(pushFront, ElementList2_NewElement11)
{
  set();
  LIST* list = &node[0];

  pushFront(&list, &node[1]);

  EXPECT_EQ(list->prev, &node[1]);
  EXPECT_EQ(strcmp(list->prev->value, "11"), 0);
}

TEST(pushFront, ElementList3_NewElement22)
{
  set();
  LIST* list = &node[0];
  list->prev = &node[1];
  node[1].next = list;

  pushFront(&list, &node[2]);

  EXPECT_EQ(list->prev->prev, &node[2]);
  EXPECT_EQ(strcmp(list->prev->prev->value, "22"), 0);
}

TEST(pushBack, EmptyList1_NewElement0)
{
set();
  LIST* list = NULL;

  pushBack(&list, &node[0]);
  EXPECT_EQ(list, &node[0]);
  EXPECT_EQ(strcmp(list->value, "00"), 0);
}

TEST(pushBack, ElementList2_NewElement11)
{
set();
  LIST* list = &node[0];

  pushBack(&list, &node[1]);

  EXPECT_EQ(list->next, &node[1]);
  EXPECT_EQ(strcmp(list->next->value, "11"), 0);
}

TEST(pushBack, ElementList3_NewElement22)
{
set();
  LIST* list = &node[0];
  list->next = &node[1];
  node[1].prev = list;

  pushBack(&list, &node[2]);

  EXPECT_EQ(list->next->next, &node[2]);
  EXPECT_EQ(strcmp(list->next->next->value, "22"), 0);
}

TEST(popFront, EmptyList_returnError)
{
set();
  LIST* list = NULL;
  char str[MAX_SIZE];
  popFront(&list, str);
  EXPECT_EQ(strcmp(str, ""), 0);
}

TEST(popFront, ElementList2_returnElement)
{
set();
  LIST* list = createList("tmp");
  char str[MAX_SIZE];
  popFront(&list, str);

  EXPECT_EQ(strcmp(str, "tmp"), 0);
  EXPECT_EQ(list, (LIST *)NULL);
}

TEST(popFront, MoreElementLis3t_returnElement)
{
  set();
  char str[MAX_SIZE];
  LIST* list = &node[0];
  list->prev = createList("tmp");
  list->prev->next = list;

  popFront(&list, str);
  EXPECT_EQ(strcmp(str, "tmp"), 0);
  EXPECT_EQ(strcmp(list->value, "00"), 0);
}

TEST(InsertBefore, ElementList1_returnTrue)
{
set();
  LIST* list = &node[0];

  InsertBefore(list, &node[1]);
  EXPECT_EQ(strcmp(list->prev->value, "11"), 0);
}

TEST(InsertBefore, ElementList2_AddedElement22)
{
set();
  LIST* list = &node[0];
  list->next = &node[1];
  node[1].prev = list;
  InsertBefore(list->next, &node[2]);
  EXPECT_EQ(strcmp(list->next->value, "22"), 0);
}

TEST(Sort, EmtpyList1_returnNullptr)
{
set();
  LIST* list = NULL;
  EXPECT_EQ(Sort(list), 0);
}

TEST(Sort, ElementList2_returnElement)
{
set();
  LIST* list = &node[0];
  Sort(list);
  EXPECT_EQ(strcmp(list->value, "00"), 0);
}

TEST(Sort, MorethenOneElementList_returnSortedList)
{
set();
  int mas[] = { 4, 2, 3, 1, 5, 0 };

  LIST* list = &node[0];
  for (int i = 0; i < 5; i++)
  {
    node[mas[i]].next = &node[mas[i + 1]];
    node[mas[i + 1]].prev = &node[mas[i]];
  }
  Sort(list);

  EXPECT_EQ(list->prev, (LIST *)NULL);
  while (list->next != NULL)
  {
    EXPECT_EQ(!(strcmp(list->value, list->next->value) - 1), 0);
    list = list->next;
  }
}
