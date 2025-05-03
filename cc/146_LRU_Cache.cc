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

#include "gtest/gtest.h"

namespace {
class LRUCache {
   public:
    LRUCache(int capacity)
        : m_capacity(capacity),
          m_p_cache_list_head(new CacheNode()),
          m_p_cache_list_near(new CacheNode()) {
      m_p_cache_list_head->m_next = m_p_cache_list_near;
      m_p_cache_list_head->m_pre = nullptr;
      m_p_cache_list_near->m_pre = m_p_cache_list_head;
      m_p_cache_list_near->m_next = nullptr;
    }

    ~LRUCache() {
        CacheNode* p = nullptr;
        p = m_p_cache_list_head->m_next;

        while (p != nullptr) {
          delete p->m_pre;
          p = p->m_next;
        }
        delete m_p_cache_list_near;

        m_map.clear();
    }

    [[nodiscard]] int Get(int key) {
        if (m_map.find(key) != m_map.end()) {
            CacheNode* p = m_map[key];
            DetachNode(p);
            AddFristNode(p);
            return (m_map[key]->m_value);
        }
        return -1;
    }

    void Put(int key, int value) {
        if (m_map.find(key) != m_map.end()) {
          m_map[key]->m_value = value;
          DetachNode((CacheNode*)m_map[key]);
          AddFristNode((CacheNode*)m_map[key]);
          if (m_map.size() > m_capacity) {
            DelEndNode();
          }

        } else {
            auto* p = new CacheNode();
            p->m_k = key;
            p->m_value = value;
            AddFristNode(p);
            m_map[key] = p;
            if (m_map.size() > m_capacity) {
                DelEndNode();
            }
        }
        return;
    }

   private:
    using CacheNode = struct Node {
      int m_k;
      int m_value;

      struct Node* m_next;
      struct Node* m_pre;
    };

    unsigned int m_capacity;
    CacheNode* m_p_cache_list_head;
    CacheNode* m_p_cache_list_near;
    std::map<int, CacheNode*> m_map;

    void DetachNode(CacheNode* node) {
      node->m_pre->m_next = node->m_next;
      node->m_next->m_pre = node->m_pre;
    }

    void AddFristNode(CacheNode* node) {
      node->m_pre = m_p_cache_list_head;

      if (m_map.empty()) {
        node->m_next = m_p_cache_list_near;
        m_p_cache_list_near->m_pre = node;
        m_p_cache_list_head->m_next = node;
      } else {
        node->m_next = m_p_cache_list_head->m_next;
        m_p_cache_list_head->m_next->m_pre = node;
        m_p_cache_list_head->m_next = node;
      }
    }
    void DelEndNode() {
      CacheNode* p = m_p_cache_list_near->m_pre;
      DetachNode(p);
      m_map.erase(p->m_k);
      delete p;
    }
};

// doubly LinkedList Node
class Node {
   public:
    int m_key{};
    int m_val{};
    Node* m_next = nullptr;
    Node* m_prev = nullptr;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

TEST(LRU_Cache, t1) {
    LRUCache obj(10);
    const int param_1 = obj.Get(1);
    (void)param_1;
    obj.Put(1, 10);
}

TEST(LRU_Cache, t2) {
    LRUCache lru(2);
    lru.Put(1, 1);             // {1,1}
    lru.Put(2, 2);             // {2,2}
    EXPECT_EQ(lru.Get(1), 1);  // {1,1} {2,2}
    lru.Put(3, 3);
    const int ret = lru.Get(2);  // {1,1} {3,3}
    EXPECT_EQ(ret, -1);

    lru.Put(4, 4);              // {4,4} {3,3}
    EXPECT_EQ(lru.Get(1), -1);  // {}
    EXPECT_EQ(lru.Get(3), 3);   // {}
    EXPECT_EQ(lru.Get(4), 4);   // {}
}

}  // namespace
