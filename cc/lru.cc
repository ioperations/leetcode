//
// Created by ioperations on 2023/5/19.
//

#include <exception>
#include <map>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {

template <typename T>
class Optional {
   public:
    Optional() : has_value(false) {}
    [[maybe_unused]] Optional(T v) : value(v) { has_value = true; }
    operator bool() { return has_value; }
    operator T() {
        if (!has_value) {
            throw std::exception();
        }
        return value;
    }
    bool operator==(const int v) const {
        if (has_value) {
            return value == v;
        }
        return false;
    }

   private:
    bool has_value = false;
    T value;
};

template <typename K, typename V>
class LRUCache final {
   public:
    LRUCache(int capability) : capability(capability) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->pre = head;
        head->pre = nullptr;
        tail->next = nullptr;
    }

    ~LRUCache() {
        Node *p = head;
        while (p) {
            Node *q = p;
            p = p->next;
            delete q;
        }
    }

    Optional<V> Get(const K &key) {
        if (map.find(key) != map.end()) {
            DelNode(map[key]);
            AddToFirstNode(map[key]);
            return map[key]->value;
        }
        return Optional<V>();
    }

    void Set(const K &key, const V &value) {
        if (map.find(key) != map.end()) {
            map[key]->value = value;
            DelNode(map[key]);
            AddToFirstNode((map[key]));
        } else {
            Node *p = new Node();
            p->key = key;
            p->value = value;

            map[key] = p;
            AddToFirstNode(p);
            if (map.size() > capability) {
                DelLastNode();
            }
        }
    }

   private:
    struct Node {
        K key;
        V value;
        Node *pre;
        Node *next;
    };

    void AddToFirstNode(Node *node) {
        head->next->pre = node;
        node->pre = head;
        node->next = head->next;
        head->next = node;
    }

    void DelNode(Node *node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void DelLastNode() {
        Node *p = tail->pre;

        tail->pre = p->pre;
        p->pre->next = tail;

        map.erase(p->key);
        delete p;
    }

    Node *head;
    Node *tail;
    std::map<K, Node *> map;
    int capability;
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
