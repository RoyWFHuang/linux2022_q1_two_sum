/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct {
    int capacity, count;
    struct list_head dhead, hheads[];
} LRUCache;

typedef struct {
    int key, value;
    struct list_head hlink, dlink;
} LRUNode;

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *obj = malloc(sizeof(*obj) + capacity * sizeof(struct list_head));
    obj->count = 0;
    obj->capacity = capacity;
    INIT_LIST_HEAD(&obj->dhead);
    for (int i = 0; i < capacity; i++)
        INIT_LIST_HEAD(&obj->hheads[i]);
    return obj;
}

void lRUCacheFree(LRUCache *obj)
{
    LRUNode *lru, *n;
    list_for_each_entry_safe (lru, n, &obj->dhead, dlink) {
        list_del(&lru->dlink);
        free(lru);
    }
    free(obj);
}

int lRUCacheGet(LRUCache *obj, int key)
{
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry (lru, &obj->hheads[hash], hlink) {
        if (lru->key == key) {
            list_move(&lru->dlink, &obj->dhead);
            return lru->value;
        }
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    LRUNode *lru;
    int hash = key % obj->capacity;
    list_for_each_entry (lru, &obj->hheads[hash], hlink) {
        if (lru->key == key) {
            list_move(&lru->dlink, &obj->dhead);
            lru->value = value;
            return;
        }
    }

    if (obj->count == obj->capacity) {
        lru = list_last_entry(&obj->dhead, LRUNode, dlink);
        list_del(&lru->dlink);
        list_del(&lru->hlink);
    } else {
        lru = malloc(sizeof(LRUNode));
        obj->count++;
    }
    lru->key = key;
    list_add(&lru->dlink, &obj->dhead);
    list_add(&lru->hlink, &obj->hheads[hash]);
    lru->value = value;
}


static void __test1()
{
    int ret;
    LRUCache *lRUCache = lRUCacheCreate(2);
    printf("NULL ");
    lRUCachePut(lRUCache, 1, 1);
    printf("NULL ");
    lRUCachePut(lRUCache, 2, 2);
    printf("NULL ");
    ret = lRUCacheGet(lRUCache, 1);
    printf("%d ", ret);
    lRUCachePut(lRUCache, 3, 3);
    printf("NULL ");
    ret = lRUCacheGet(lRUCache, 2);
    printf("%d ", ret);
    lRUCachePut(lRUCache, 4, 4);
    printf("NULL ");
    ret = lRUCacheGet(lRUCache, 1);
    printf("%d ", ret);
    ret = lRUCacheGet(lRUCache, 3);
    printf("%d ", ret);
    ret = lRUCacheGet(lRUCache, 4);
    printf("%d ", ret);
}

int main()
{
    __test1();
    return 0;
}
