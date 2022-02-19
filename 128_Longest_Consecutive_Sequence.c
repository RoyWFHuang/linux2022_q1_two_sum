#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct seq_node {
    int num;
    struct list_head link;
};

static struct seq_node *find(int num, int size, struct list_head *heads)
{
    struct seq_node *node;
    int hash = num < 0 ? -num % size : num % size;
    list_for_each_entry (node, &heads[hash], link) {
        if (node->num == num)
            return node;
    }
    return NULL;
}

int longestConsecutive(int *nums, int n_size)
{
    int hash, length = 0;
    struct seq_node *node;
    struct list_head *heads = malloc(n_size * sizeof(*heads));

    for (int i = 0; i < n_size; i++)
        INIT_LIST_HEAD(&heads[i]);

    for (int i = 0; i < n_size; i++) {
        if (!find(nums[i], n_size, heads)) {
            hash = nums[i] < 0 ? -nums[i] % n_size : nums[i] % n_size;
            node = malloc(sizeof(*node));
            node->num = nums[i];
            list_add(&node->link, &heads[hash]);
        }
    }

    for (int i = 0; i < n_size; i++) {
        int len = 0;
        int num;
        node = find(nums[i], n_size, heads);
        // printf("%d\n", nums[i]);
        while (node) {
            len++;
            // num = node->num;
            // printf("num = %d\n", num);
            list_del(&node->link);

            int left = nums[i], right = nums[i];
            while ((node = find(--left, n_size, heads))) {
                len++;
                list_del(&node->link);
            }

            while ((node = find(++right, n_size, heads))) {
                len++;
                list_del(&node->link);
            }

            length = len > length ? len : length;
        }
    }

    return length;
}



static void __test1()
{
    int a[] = {100, 4, 200, 1, 3, 2};
    int ret = 0;
    ret = longestConsecutive(a, 6);
    printf("%d\n", ret);
}

static void __test2()
{
    int ret = 0;
    int b[] = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    ret = longestConsecutive(b, 10);
    printf("%d\n", ret);
}


int main()
{
    __test1();
    __test2();
    return 0;
}
