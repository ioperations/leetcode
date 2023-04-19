// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Design a data structure that follows the constraints of a Least Recently Used
(LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return
-1. void put(int key, int value) Update the value of the key if the key exists.
Otherwise, add the key-value pair to the cache. If the number of keys exceeds
the capacity from this operation, evict the least recently used key. The
functions get and put must each run in O(1) average time complexity.
*/

#include <map>

class LRUCache {
   public:
    LRUCache(int capacity) : capacity(capacity) {
        p_cache_list_head = new CacheNode();
        p_cache_list_near = new CacheNode();
        p_cache_list_head->next = p_cache_list_near;
        p_cache_list_head->pre = nullptr;
        p_cache_list_near->pre = p_cache_list_head;
        p_cache_list_near->next = nullptr;
    }

    ~LRUCache() {
        CacheNode *p;
        p = p_cache_list_head->next;

        while (p != nullptr) {
            delete p->pre;
            p = p->next;
        }
        delete p_cache_list_near;

        map.clear();
    }

    int Get(int key) {
        if (map.find(key) != map.end()) {
            CacheNode *p = map[key];
            DetachNode(p);
            AddFristNode(p);
            return (map[key]->value);
        }
        return -1;
    }

    void Put(int key, int value) {
        if (map.find(key) != map.end()) {
            map[key]->value = value;
            DetachNode((CacheNode *)map[key]);
            AddFristNode((CacheNode *)map[key]);
            if (map.size() > capacity) {
                DelEndNode();
            }

        } else {
            CacheNode *p = new CacheNode();
            p->k = key;
            p->value = value;
            AddFristNode(p);
            map[key] = p;
            if (map.size() > capacity) {
                DelEndNode();
            }
        }
        return;
    }

   private:
    typedef struct Node {
        int k;
        int value;

        struct Node *next;
        struct Node *pre;
    } CacheNode;

    unsigned int capacity;
    CacheNode *p_cache_list_head;
    CacheNode *p_cache_list_near;
    std::map<int, CacheNode *> map;

    void DetachNode(CacheNode *node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void AddFristNode(CacheNode *node) {
        node->pre = p_cache_list_head;

        if (map.empty()) {
            node->next = p_cache_list_near;
            p_cache_list_near->pre = node;
            p_cache_list_head->next = node;
        } else {
            node->next = p_cache_list_head->next;
            p_cache_list_head->next->pre = node;
            p_cache_list_head->next = node;
        }
    }
    void DelEndNode() {
        CacheNode *p = p_cache_list_near->pre;
        DetachNode(p);
        map.erase(p->k);
        delete p;
    }
};

// doubly LinkedList Node
class Node {
   public:
    int key;
    int val;
    Node *next = nullptr;
    Node *prev = nullptr;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    LRUCache *obj = new LRUCache(10);
    int param_1 = obj->Get(1);
    (void)param_1;
    obj->Put(1, 10);

    delete obj;
}

TEST(t0, t2) {
    LRUCache *lru = new LRUCache(2);
    lru->Put(1, 1);             // {1,1}
    lru->Put(2, 2);             // {2,2}
    EXPECT_EQ(lru->Get(1), 1);  // {1,1} {2,2}
    lru->Put(3, 3);
    int ret = lru->Get(2);  // {1,1} {3,3}
    EXPECT_EQ(ret, -1);

    lru->Put(4, 4);              // {4,4} {3,3}
    EXPECT_EQ(lru->Get(1), -1);  // {}
    EXPECT_EQ(lru->Get(3), 3);   // {}
    EXPECT_EQ(lru->Get(4), 4);   // {}
    // ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get",
    // "get"]
    // [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
    // Output [null, null, null, 1, null, -1, null, -1, 3, 4]

    delete lru;
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
