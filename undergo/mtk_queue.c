#include <stdio.h>
#include <stdlib.h>

typedef struct __node {
    int value;
    struct __node *next;
} Node;

typedef struct __list {
    Node *head;
    Node **next;
} List;

int list_new(List **ret)
{
    void *list = NULL;
    list = malloc(sizeof(List));
    if (list) {
        memset(list, 0, sizeof(List));
        list->next = &list->head;
        *ret = (List*)list; 
        return 0;
    } else {
        return -1;
    }
}

int list_enqueue(List *list, Node *node)
{
    if (!list || !node) return -1;
    *list->next = node;
    list->next = &node->next;
    return 0;
}

Node *list_dequeue(List *list)
{
    if (!list || !list->head) {
        return NULL;
    }
    Node *ret = List->head;
    list->head = list->head->next;
    return ret;
}

int main()
{
    List *list;
    list_new(&list);
    if (!list) {
        printf("malloc fail\n");
        return -1;
    }

    Node *node;
    node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("malloc node fail\n");
        return -1;
    }
    node->value = 1;
    list_enqueue(list, node);
    
    Node *ret = list_dequeue(list);
    if (ret)

}
