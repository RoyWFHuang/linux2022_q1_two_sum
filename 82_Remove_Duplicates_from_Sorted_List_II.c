/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};


static void additem(struct ListNode **head, struct ListNode *node)
{
    struct ListNode **tmp = head;
    if (!*head) {
        *head = node;
        return;
    }
    while ((*tmp)->next) {
        tmp = &(*tmp)->next;
    }
    (*tmp)->next = node;
    return;
}

struct ListNode *deleteDuplicates(struct ListNode *head)
{
    if (!head)
        return NULL;

    if (head->next && head->val == head->next->val) {
        /* Remove all duplicate numbers */
        while (head->next && head->val == head->next->val)
            head = head->next;
        return deleteDuplicates(head->next);
    }

    head->next = deleteDuplicates(head->next);

    return head;
}

static void __test1()
{
    struct ListNode *head = NULL;
    struct ListNode *ret;
    struct ListNode *node = NULL;
    int val_arr[] = {1, 2, 3, 3, 4, 4, 5};
    int arr_len = sizeof(val_arr) / sizeof(int);


    printf("add ");
    for (int i = 0; i < arr_len; i++) {
        node = calloc(1, sizeof(struct ListNode));
        printf("%d ", val_arr[i]);
        node->val = val_arr[i];
        additem(&head, node);
    }
    printf("\n");
    ret = deleteDuplicates(head);
    // printf("ret = %p\n", ret);
    printf("[");
    for (struct ListNode *tmp = ret; tmp != NULL; tmp = tmp->next)
        printf("%d ", tmp->val);
    printf("]\n");
}

static void __test2()
{
    struct ListNode *head = NULL;
    struct ListNode *ret;
    struct ListNode *node = NULL;
    int val_arr[] = {1, 1, 1, 2, 3};
    int arr_len = sizeof(val_arr) / sizeof(int);


    printf("add ");
    for (int i = 0; i < arr_len; i++) {
        node = calloc(1, sizeof(struct ListNode));
        printf("%d ", val_arr[i]);
        node->val = val_arr[i];
        additem(&head, node);
    }
    printf("\n");
    ret = deleteDuplicates(head);
    // printf("ret = %p\n", ret);
    printf("[");
    for (struct ListNode *tmp = ret; tmp != NULL; tmp = tmp->next)
        printf("%d ", tmp->val);
    printf("]\n");
}


int main()
{
    __test1();
    __test2();
    return 0;
}
