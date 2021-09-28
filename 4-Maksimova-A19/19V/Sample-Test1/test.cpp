#include "pch.h"
extern "C"
{
#include "nineteen.h"
}


LIST* CreateTestList(char new1[], char new2[], char new3[], char new4[], char new5[], char new6[])
{
    LIST* list = (LIST*)malloc(sizeof(LIST));
    NODE* A = (NODE*)malloc(sizeof(NODE));
    NODE* B = (NODE*)malloc(sizeof(NODE));
    NODE* C = (NODE*)malloc(sizeof(NODE));
    NODE* D = (NODE*)malloc(sizeof(NODE));
    NODE* E = (NODE*)malloc(sizeof(NODE));
    NODE* F = (NODE*)malloc(sizeof(NODE));

    list->head = A;
    list->tail = F;

    A->next = B;
    B->next = C;
    C->next = D;
    D->next = E;
    E->next = F;
    F->next = NULL;

    A->prev = NULL;
    B->prev = A;
    C->prev = B;
    D->prev = C;
    E->prev = D;
    F->prev = E;

    strcpy(A->value.value, new1);
    strcpy(B->value.value, new2);
    strcpy(C->value.value, new3);
    strcpy(D->value.value, new4);
    strcpy(E->value.value, new5);
    strcpy(F->value.value, new6);

    return list;
}

TEST(pushFront, EmptyList1_returnTrue) {
    LIST* p = createList();

    pushFront(p, "newel0");
    EXPECT_EQ(p->head, p->tail);
    EXPECT_EQ(strcmp(p->head->value.value, "newel0"), 0);
    deleteList(&p);
}

TEST(pushFront, ElementList2_returnTrue) {
    LIST* p = createList();
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    char new0[300] = "newel00";
    p->head = p->tail = tmp;
    strcpy(tmp->value.value, new0);
    tmp->prev = tmp->next = NULL;

    pushFront(p, "newel10");
    EXPECT_EQ(p->head->next, p->tail);
    EXPECT_EQ(strcmp(p->head->value.value, "newel10"), 0);
    EXPECT_EQ(strcmp(p->tail->prev->value.value, "newel10"), 0);
    deleteList(&p);
}

TEST(pushFront, ElementList3_returnTrue) {
    LIST* p = createList();
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    NODE* q = (NODE*)malloc(sizeof(NODE));
    char new1[300] = "newel00";
    char new2[300] = "newel10";
    p->head = tmp;
    p->tail = q;
    tmp->prev = q->next = NULL;
    tmp->next = q;
    q->prev = tmp;
    strcpy(tmp->value.value, new1);
    strcpy(q->value.value, new2);

    pushFront(p, "newel20");
    EXPECT_EQ(p->head->next, p->tail->prev);
    EXPECT_EQ(strcmp(p->head->value.value, "newel20"), 0);
    EXPECT_EQ(strcmp(p->tail->prev->prev->value.value, "newel20"), 0);
    deleteList(&p);
}

TEST(pushBack, EmptyList1_returnTrue) {
    LIST* p = createList();

    pushBack(p, "newel00");
    EXPECT_EQ(p->head, p->tail);
    EXPECT_EQ(strcmp(p->tail->value.value, "newel00"), 0);
    deleteList(&p);
}

TEST(pushBack, ElementList2_returnTrue) {
    LIST* p = createList();
    NODE* q = (NODE*)malloc(sizeof(NODE));
    char new0[300] = "newel00";
    p->head = p->tail = q;
    strcpy(q->value.value, new0);
    q->prev = q->next = NULL;

    pushBack(p, "newel10");
    EXPECT_EQ(p->tail->prev, p->head);
    EXPECT_EQ(strcmp(p->tail->value.value, "newel10"), 0);
    EXPECT_EQ(strcmp(p->head->next->value.value, "newel10"), 0);
    deleteList(&p);
}

TEST(pushBack, ElementList3_returnTrue) {
    LIST* p = createList();
    NODE* A = (NODE*)malloc(sizeof(NODE));
    NODE* B = (NODE*)malloc(sizeof(NODE));
    char new1[300] = "newel0";
    char new2[300] = "newel10";
    p->head = A;
    p->tail = B;
    A->prev = B->next = NULL;
    A->next = B;
    B->prev = A;
    strcpy(A->value.value, new1);
    strcpy(B->value.value, new2);

    pushBack(p, "newel20");
    EXPECT_EQ(p->head->next, p->tail->prev);
    EXPECT_EQ(strcmp(p->tail->value.value, "newel20"), 0);
    EXPECT_EQ(strcmp(p->head->next->next->value.value, "newel20"), 0);
    deleteList(&p);
}

TEST(popFront, EmptyList_returnError) {
    LIST* p = createList();
    EXPECT_EQ(strcmp(popFront(p).value, ""), 0);
    deleteList(&p);
}

TEST(popFront, ElementList2_returnElement) {
    LIST* p = createList();
    DATA tmp = { 0 };
    NODE* q = (NODE*)malloc(sizeof(NODE));
    char new0[300] = "newel0";
    p->head = p->tail = q;
    strcpy(q->value.value, new0);
    q->prev = q->next = NULL;

    tmp = popFront(p);
    EXPECT_EQ(strcmp(tmp.value, "newel0"), 0);
    EXPECT_EQ(p->head, nullptr);
    deleteList(&p);
}

TEST(popFront, MoreElementLis3t_returnElement) {
    LIST* p = createList();
    DATA tmp = { 0 };
    NODE* A = (NODE*)malloc(sizeof(NODE));
    NODE* B = (NODE*)malloc(sizeof(NODE));
    char new1[300] = "newel0";
    char new2[300] = "newel10";
    p->head = A;
    p->tail = B;
    A->prev = B->next = NULL;
    A->next = B;
    B->prev = A;
    strcpy(A->value.value, new1);
    strcpy(B->value.value, new2);

    tmp = popFront(p);
    EXPECT_EQ(strcmp(tmp.value, "newel0"), 0);
    EXPECT_EQ(strcmp(p->head->value.value, "newel10"), 0);
    EXPECT_EQ(p->head, p->tail);
    deleteList(&p);
}

TEST(InsertBefore, ElementList1_returnTrue) {
    LIST* p = createList();

    DATA tmp = { 0 };
    NODE* q = (NODE*)malloc(sizeof(NODE));
    char new0[300] = "newel0";
    p->head = p->tail = q;
    strcpy(q->value.value, new0);
    q->prev = q->next = NULL;

    NODE* q2 = p->head;
    InsertBefore(p, q2, "newel0");
    EXPECT_EQ(strcmp(p->head->value.value, "newel0"), 0);
    EXPECT_EQ(p->head->next, p->tail);
    deleteList(&p);
}

TEST(InsertBefore, ElementList2_returnTrue) {
    LIST* p = createList();
    NODE* A = (NODE*)malloc(sizeof(NODE));
    NODE* B = (NODE*)malloc(sizeof(NODE));
    char new1[300] = "newel0";
    char new2[300] = "newel10";
    p->head = A;
    p->tail = B;
    A->prev = B->next = NULL;
    A->next = B;
    B->prev = A;
    strcpy(A->value.value, new1);
    strcpy(B->value.value, new2);

    NODE* q2 = p->tail;
    InsertBefore(p, q2, "newel0");
    EXPECT_EQ(strcmp(p->tail->prev->value.value, "newel0"), 0);
    EXPECT_EQ(p->head->next, p->tail->prev);
    deleteList(&p);
}

TEST(InsertBefore, MoreElementList3_returnTrue) {
    LIST* p = CreateTestList("newel10", "newel20", "newel30", "newel40", "newel60", "newel70");
    NODE* q2 = p->tail->prev;
    InsertBefore(p, q2, "newel50");
    EXPECT_EQ(strcmp(p->tail->value.value, "newel70"), 0);
    EXPECT_EQ(strcmp(p->tail->prev->prev->value.value, "newel50"), 0);
    deleteList(&p);
}

TEST(Sort, EmtpyList1_returnNullptr) {
    LIST* p = createList();
    EXPECT_EQ(Sort(&p), 0);
}

TEST(Sort, ElementList2_returnElement) {
    LIST* p = createList();
    NODE* q = (NODE*)malloc(sizeof(NODE));
    char new0[300] = "newel0";
    p->head = p->tail = q;
    strcpy(q->value.value, new0);
    q->prev = q->next = NULL;
    Sort(&p);
    EXPECT_EQ(strcmp(p->head->value.value, "newel0"), 0);
}

TEST(Sort_MorethenOneElementList_returnSortedLint) {
    char unsortedListElem[LIST_SIZE][MAX_SIZE] = { "hjbmn0","cdjfs0","abnghjk0","12sdfg0","abchjk0","ghjk0" };
    char sortedListElem[LIST_SIZE][MAX_SIZE] = { "12sdfg0","abchjk0","abnghjk0","cdjfs0","ghjk0","hjbmn0" };
    LIST* p = CreateTestList("hjbmn0", "cdjfs0", "abnghjk0", "12sdfg0", "abchjk0", "ghjk0");
    Sort(&p);
    NODE* cmp = p->head;
    for (int i = 0; i < LIST_SIZE; i++) {
        EXPECT_EQ(strcmp(cmp->value.value, sortedListElem[i]), 0);
        cmp = cmp->next;
    }
}