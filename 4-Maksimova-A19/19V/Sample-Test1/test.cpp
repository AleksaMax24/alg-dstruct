#include "pch.h"
extern "C"
{
#define MAX_SIZE 15
#include "nineteentwo.h"
}


LIST node[6];

void set(void)
{
    for (int i = 0; i < 6; i++) {
        node[i].next = node[i].prev = NULL;
    }
    node[0].value = "00";
    node[1].value = "11";
    node[2].value = "22";
    node[3].value = "33";
    node[4].value = "44";
    node[5].value = "55";
}

TEST(CreateList_Test, CreateList_e) {

    LIST* list = createList("tmp");
    EXPECT_EQ(strcmp(list->value, "tmp"), 0);
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
    LIST* list = NULL;
    char str[MAX_SIZE];
    popFront(&list, str);
    EXPECT_EQ(strcmp(str, ""), 0);
}

TEST(popFront, ElementList2_returnElement)
{
    set();
    LIST* list = &node[0];
    char str[MAX_SIZE];
    popFront(&list, str);

    EXPECT_EQ(strcmp(str, "00"), 0);
    EXPECT_EQ(list, (LIST*)NULL);
}

TEST(popFront, MoreElementLis3t_returnElement)
{
    set();
    char str[MAX_SIZE];
    LIST* list = &node[1];
    list->prev = &node[0];
    list->prev->next = list;

    popFront(&list, str);
    EXPECT_EQ(strcmp(str, "00"), 0);
    EXPECT_EQ(strcmp(list->value, "11"), 0);
}

TEST(insertBefore, ElementList1_returnTrue)
{
    set();
    LIST* list = &node[0];

    insertBefore(list, &node[1]);
    EXPECT_EQ(strcmp(list->prev->value, "11"), 0);
}

TEST(insertBefore, ElementList2_returnTrue)
{
    set();
    LIST* list = &node[0];
    list->next = &node[1];
    node[1].prev = list;
    insertBefore(list->next, &node[2]);
    EXPECT_EQ(strcmp(list->next->value, "22"), 0);
}

TEST(Sort, EmtpyList1_returnNullptr)
{
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

TEST(Sort, MorethenOneElementList1_returnSortedList)
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

    EXPECT_EQ(list->prev, (LIST*)NULL);
    while (list->next != NULL)
    {
        EXPECT_EQ(!(strcmp(list->value, list->next->value) - 1), 0);
        list = list->next;
    }
}

TEST(Sort, MorethenOneElementList2_returnSortedList)
{
    set();
    int mas[] = { 0, 1, 2, 3, 4, 5 };

    LIST* list = &node[0];
    for (int i = 0; i < 5; i++)
    {
        node[mas[i]].next = &node[mas[i + 1]];
        node[mas[i + 1]].prev = &node[mas[i]];
    }
    Sort(list);

    EXPECT_EQ(list->prev, (LIST*)NULL);
    while (list->next != NULL)
    {
        EXPECT_EQ(!(strcmp(list->value, list->next->value) - 1), 0);
        list = list->next;
    }
}

TEST(Sort, MorethenOneElementList3_returnSortedList)
{
    set();
    int mas[] = { 5, 4, 3, 2, 1, 0 };

    LIST* list = &node[0];
    for (int i = 0; i < 5; i++)
    {
        node[mas[i]].next = &node[mas[i + 1]];
        node[mas[i + 1]].prev = &node[mas[i]];
    }
    Sort(list);

    EXPECT_EQ(list->prev, (LIST*)NULL);
    while (list->next != NULL)
    {
        EXPECT_EQ(!(strcmp(list->value, list->next->value) - 1), 0);
        list = list->next;
    }
}
