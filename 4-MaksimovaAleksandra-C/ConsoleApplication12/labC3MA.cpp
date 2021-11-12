#include <stdio.h>
#include <stdlib.h>


#define GREAT 1
#define FAIL 0

typedef struct{
    int* arr;
    int size;
    int head;
    int tail;
} queue_t;

typedef struct{
    int num_ed;
    int* edges;
} node_t;

typedef struct{
    int num_nod;
    node_t* nodes;
} adj_list_t;

int InitQueue(queue_t* q, int size){
    q->arr = NULL;

    if (size > 0) 
    {
        q->arr = (int*)calloc(size, sizeof(int));
    }

    if (q->arr)
    {
        q->size = size;
        q->head = 0;
        q->tail = 0;

        return GREAT;
    }

    return FAIL;
}

int Put(queue_t* q, int newEl){
    if (q->arr != NULL && q->size > q->tail)
    {
        q->arr[q->tail++] = newEl;

        return GREAT;
    }

    return FAIL;
}

int Get(queue_t* q, int* oldEl){
    if (q != NULL && q->head != q->tail)
    {
        *oldEl = q->arr[q->head++];

        return GREAT;
    }

    return FAIL;
}

void DelQueue(queue_t* q){
    free(q->arr);
    q->arr = NULL;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

int BFS(adj_list_t* list, queue_t* q){
    int counter;
    int cur_nod;
    int* used = (int*)calloc(list->num_nod, sizeof(int));

    if (list->num_nod != 0 && list->nodes != NULL && q->arr != NULL && list->num_nod <= q->size && used != NULL)
    {
        Put(q, 0);
        used[0] = 1;

        while (Get(q, &cur_nod))
        {
            for (counter = 0; counter < list->nodes[cur_nod].num_ed; counter++)
                if (!used[list->nodes[cur_nod].edges[counter]]) 
                {
                    Put(q, list->nodes[cur_nod].edges[counter]);
                    used[list->nodes[cur_nod].edges[counter]] = 1;
                }
        }

        free(used);
        return GREAT;
    }

    free(used);
    return FAIL;
}

void ReadAdjList(adj_list_t* list){
    int counter;
    int cur_nod, tmp_nod;
    char ch;

    for (counter = 0; counter < list->num_nod; counter++) 
    {
        scanf("%i%c", &cur_nod, &ch);

        while (ch == ' ')
        {
            scanf("%i%c", &tmp_nod, &ch);
            list->nodes[cur_nod].edges[list->nodes[cur_nod].num_ed++] = tmp_nod;
            list->nodes[tmp_nod].edges[list->nodes[tmp_nod].num_ed++] = cur_nod;
        }
    }
}

int main(void){
    int counter1, counter2;
    adj_list_t list;
    queue_t q;
    queue_t* qptr = &q;

    scanf("%i", &list.num_nod);

    if (!InitQueue(qptr, list.num_nod))
        return 0;

    list.nodes = (node_t*)calloc(list.num_nod, sizeof(node_t));

    if (!list.nodes)
    {
        DelQueue(qptr);
        return 0;
    }

    for (counter1 = 0; counter1 < list.num_nod; counter1++) 
    {
        list.nodes[counter1].edges = (int*)calloc(list.num_nod, sizeof(int));

        if (!list.nodes[counter1].edges) {
            for (counter2 = 0; counter2 < counter1; counter2++)
                free(list.nodes[counter2].edges);

            free(list.nodes);
            DelQueue(qptr);
            return 0;
        }
    }

    ReadAdjList(&list);

    BFS(&list, qptr);

    for (counter1 = 0; counter1 < q.tail; counter1++)
        printf("%i ", q.arr[counter1]);

    for (counter1 = 0; counter1 < list.num_nod; counter1++)
    {
        free(list.nodes[counter1].edges);
    }
    free(list.nodes);
    DelQueue(qptr);
    return 0;
}
