//
// Created by ioperations on 2023/5/19.
//

#include <exception>
#include <map>

#include "gtest/gtest.h"

namespace {

template <typename T>
class Optional {
   public:
    Optional() : m_value() {}
    [[maybe_unused]] Optional(T v) : has_value(true), m_value(v) {}
    operator bool() { return has_value; }
    operator T() {
        if (!has_value) {
            throw std::exception();
        }
        return m_value;
    }
    bool operator==(const int v) const {
        if (has_value) {
          return m_value == v;
        }
        return false;
    }

   private:
    bool has_value = false;
    T m_value;
};

template <typename K, typename V>
class LRUCache final {
   public:
    LRUCache(int capability)
        : head(new Node()), tail(new Node()), m_capability(capability) {
      head->m_next = tail;
      tail->m_pre = head;
      head->m_pre = nullptr;
      tail->m_next = nullptr;
    }

    ~LRUCache() {
        Node* p = head;
        while (p) {
            Node* q = p;
            p = p->m_next;
            delete q;
        }
    }

    Optional<V> Get(const K& key) {
      if (m_map.find(key) != m_map.end()) {
        DelNode(m_map[key]);
        AddToFirstNode(m_map[key]);
        return m_map[key]->m_value;
      }
        return Optional<V>();
    }

    void Set(const K& key, const V& value) {
      if (m_map.find(key) != m_map.end()) {
        m_map[key]->m_value = value;
        DelNode(m_map[key]);
        AddToFirstNode((m_map[key]));
      } else {
        Node* p = new Node();
        p->m_key = key;
        p->m_value = value;

        m_map[key] = p;
        AddToFirstNode(p);
        if (m_map.size() > m_capability) {
          DelLastNode();
        }
      }
    }

   private:
    struct Node {
      K m_key;
      V m_value;
      Node* m_pre;
      Node* m_next;
    };

    void AddToFirstNode(Node* node) {
      head->m_next->m_pre = node;
      node->m_pre = head;
      node->m_next = head->m_next;
      head->m_next = node;
    }

    void DelNode(Node* node) {
      node->m_pre->m_next = node->m_next;
      node->m_next->m_pre = node->m_pre;
    }

    void DelLastNode() {
      Node* p = tail->m_pre;

      tail->m_pre = p->m_pre;
      p->m_pre->m_next = tail;

      m_map.erase(p->m_key);
      delete p;
    }

    Node* head;
    Node* tail;
    std::map<K, Node*> m_map;
    int m_capability;
};

TEST(lru, t1) {
    LRUCache<int, int> lru(3);
    lru.Set(10, 10);
    lru.Set(0, 0);
    lru.Set(1, 1);
    lru.Set(2, 2);

    auto ret = lru.Get(10);
    EXPECT_EQ(!ret, true);

    ret = lru.Get(1);

    EXPECT_EQ(ret, 1);
}

}  // namespace
