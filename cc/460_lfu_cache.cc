/*
 * Design and implement a data structure for a Least Frequently Used (LFU)
cache.

Implement the LFUCache class:

    LFUCache(int capacity) Initializes the object with the capacity of the data
structure. int get(int key) Gets the value of the key if the key exists in the
cache. Otherwise, returns -1. void Put(int key, int value) Update the value of
the key if present, or inserts the key if not already present. When the cache
reaches its capacity, it should invalidate and remove the least frequently used
key before inserting a new item. For this problem, when there is a tie (i.e.,
two or more keys with the same frequency), the least recently used key would be
invalidated.

To determine the least frequently used key, a use counter is maintained for each
key in the cache. The key with the smallest use counter is the least frequently
used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to
the Put operation). The use counter for a key in the cache is incremented either
a get or put operation is called on it.

The functions get and Put must each run in O(1) average time complexity.
*/
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "gtest/gtest.h"

using namespace std;

namespace {

template <typename K, typename V>
class LFUCacheImpl {
   public:
    LFUCacheImpl() : m_min_freq(1), m_capacity(default_capacity) {}
    explicit LFUCacheImpl(int m_capacity)
        : m_min_freq(1), m_capacity(m_capacity) {}

    void Put(const K& key, const V& value) {
        if (m_key_table.find(key) != m_key_table.end()) {
            auto node = m_key_table[key];
            int freq = node->m_freq;
            m_freq_table[freq].erase(node);
            if (m_freq_table[freq].size() == 0) {
                m_freq_table.erase(freq);
                if (freq == m_min_freq) ++m_min_freq;
            }

            freq++;
            Node const tmp(key, value, freq);
            m_freq_table[freq].push_front(tmp);
            m_key_table[key] = m_freq_table[freq].begin();
        } else {
            if (m_key_table.size() == m_capacity) {
                // 提前判断缓存是否会溢出，一是顺序合理，二是防止缓存刚插入(freq
                // = 1)就被去掉
                m_key_table.erase(m_freq_table[m_min_freq].back().m_key);
                m_freq_table[m_min_freq].pop_back();
                if (m_freq_table[m_min_freq].size() == 0) {
                    m_freq_table.erase(m_min_freq);
                }
            }
            m_min_freq = 1;  // 既然插入了新元素那么minFreq自然就回归1了
            m_freq_table[1].push_front(Node(key, value, 1));
            m_key_table[key] = m_freq_table[1].begin();
        }
    }

    std::optional<V> Get(const K& key) {
        if (m_key_table.find(key) != m_key_table.end()) {
            auto node = m_key_table[key];
            int freq = node->m_freq;
            V val = node->m_val;
            m_freq_table[freq].erase(node);
            if (m_freq_table[freq].size() == 0) {
                // 如果当前频率的list空了，则要删除当前list并且判断是否需要更新minFreq
                m_freq_table.erase(freq);
                if (freq == m_min_freq) ++m_min_freq;
            }
            ++freq;
            Node const tmp(key, val, freq);
            m_freq_table[freq].push_front(tmp);
            m_key_table[key] = m_freq_table[freq].begin();
            return val;
        }
        return std::optional<V>();
    }

    void Print() {  // 打印检查
        for (auto it = m_key_table.begin(); it != m_key_table.end(); ++it) {
            std::cout << it->second->key << " " << m_min_freq << " "
                      << it->second->freq << std::endl;
        }
    }

   private:
    struct Node {
        int m_freq;
        K m_key;
        V m_val;
        Node() : m_freq(0), m_key(K()), m_val(V()) {};
        Node(const K& m_key, V m_val, int m_freq)
            : m_freq(m_freq), m_key(m_key), m_val(std::move(m_val)) {};
    };
    constexpr static int default_capacity = 50;
    unordered_map<K, typename list<Node>::iterator> m_key_table;  // 键值是key
    unordered_map<int, list<Node>> m_freq_table;  // 键值是访问频率

    int m_min_freq, m_capacity;  // 最小访问频率，缓存容量
};

template <typename K, typename V>
class LFUCache {
    LFUCache(int cap) : m_impl(cap) {}
    void Put(const K& key, const int& value) { m_impl.Put(key, value); }
    std::optional<V> Get(const K& key) { return m_impl.Get(key); }

   private:
    LFUCacheImpl<K, V> m_impl;
};

template <typename K>
class LFUCache<K, int> {
   public:
    LFUCache(int cap) : m_impl(cap) {}
    void Put(const K& key, const int& value) { m_impl.Put(key, value); }
    int Get(const K& key) {
        auto ret = m_impl.Get(key);
        if (!ret) {
            return -1;
        }
        return *ret;
    }

   private:
    LFUCacheImpl<K, int> m_impl;
};

TEST(lfu_cache, t1) {
    LFUCache<int, int> lfu(2);
    lfu.Put(1, 1);         // cache=[1,_], cnt(1)=1
    lfu.Put(2, 2);         // cache=[2,1], cnt(2)=1, cnt(1)=1
    int ret = lfu.Get(1);  // return 1
    EXPECT_EQ(ret, 1);     // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.Put(3,
            3);        // 2 is the LFU key because cnt(2)=1 is the smallest,
                       // invalidate 2. cache=[3,1], cnt(3)=1, cnt(1)=2
    ret = lfu.Get(2);  // return -1 (not found)
    EXPECT_EQ(ret, -1);
    ret = lfu.Get(3);   // return 3
    EXPECT_EQ(ret, 3);  // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.Put(4, 4);      // Both 1 and 3 have the same cnt, but 1 is LRU,
                        // invalidate 1. cache=[4,3], cnt(4)=1, cnt(3)=2
    ret = lfu.Get(1);   // return -1 (not found)
    EXPECT_EQ(ret, -1);
    ret = lfu.Get(3);   // return 3
    EXPECT_EQ(ret, 3);  // cache=[3,4], cnt(4)=1, cnt(3)=3
    ret = lfu.Get(4);   // return 4
    EXPECT_EQ(ret, 4);  // cache=[4,3], cnt(4)=2, cnt(3)=3
}

TEST(lfu_cache, t2) {
    LFUCache<int, int> lfu(3);
    lfu.Put(1, 1);         // cache=[1,_], cnt(1)=1
    lfu.Put(2, 2);         // cache=[2,1], cnt(2)=1, cnt(1)=1
    int ret = lfu.Get(1);  // return 1
    EXPECT_EQ(ret, 1);     // cache=[1,2], cnt(2)=1, cnt(1)=2
    ret = lfu.Get(2);      // return 1
    EXPECT_EQ(ret, 2);     // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.Put(3,
            3);        // 2 is the LFU key because cnt(2)=1 is the smallest,
                       // invalidate 2. cache=[3,1], cnt(3)=1, cnt(1)=2
    ret = lfu.Get(2);  // return -1 (not found)
    EXPECT_EQ(ret, 2);
    lfu.Put(4, 4);     // Both 1 and 3 have the same cnt, but 1 is LRU,
                       // invalidate 1. cache=[4,3], cnt(4)=1, cnt(3)=2
    ret = lfu.Get(1);  // return -1 (not found)
    EXPECT_EQ(ret, 1);
    ret = lfu.Get(3);    // return 3
    EXPECT_EQ(ret, -1);  // cache=[3,4], cnt(4)=1, cnt(3)=3
    ret = lfu.Get(4);    // return 4
    EXPECT_EQ(ret, 4);   // cache=[4,3], cnt(4)=2, cnt(3)=3
}

TEST(lfu_cache, t3) {
    LFUCacheImpl<int, std::string> lfu(2);
    lfu.Put(1, "1");        // cache=[1,_], cnt(1)=1
    lfu.Put(2, "2");        // cache=[2,1], cnt(2)=1, cnt(1)=1
    auto ret = lfu.Get(1);  // return 1
    EXPECT_EQ(ret, "1");    // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.Put(3,
            "3");      // 2 is the LFU key because cnt(2)=1 is the smallest,
                       // invalidate 2. cache=[3,1], cnt(3)=1, cnt(1)=2
    ret = lfu.Get(2);  // return -1 (not found)
    EXPECT_EQ(!ret, true);
    ret = lfu.Get(3);     // return 3
    EXPECT_EQ(ret, "3");  // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.Put(4, "4");      // Both 1 and 3 have the same cnt, but 1 is LRU,
                          // invalidate 1. cache=[4,3], cnt(4)=1, cnt(3)=2
    ret = lfu.Get(1);     // return -1 (not found)
    EXPECT_EQ(!ret, true);
    ret = lfu.Get(3);     // return 3
    EXPECT_EQ(ret, "3");  // cache=[3,4], cnt(4)=1, cnt(3)=3
    ret = lfu.Get(4);     // return 4
    EXPECT_EQ(ret, "4");  // cache=[4,3], cnt(4)=2, cnt(3)=3
}
}  // namespace

#ifdef TEST_ADQ
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
