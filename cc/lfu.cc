
#include <list>
#include <optional>
#include <unordered_map>

#include "gtest/gtest.h"

namespace {

template <typename K, typename V>
class LfuCache {
   public:
    LfuCache(int capablity);
    LfuCache(LfuCache&&) = default;
    LfuCache(const LfuCache&) = default;
    ~LfuCache();
    void Set(const K& key, const V& value);
    std::optional<V> Get(const K& key);

   private:
    struct Node {
        K m_key;
        V m_value;
        int m_freq;
        Node(K key, V value, int freq)
            : m_key(key), m_value(value), m_freq(freq) {}
    };
    int min_freq{1};
    int m_capablity;
    std::unordered_map<K, typename std::list<Node>::iterator>
        m_key_to_list_head;
    std::unordered_map<int, typename std::list<Node>> m_freq_to_list;
};

template <typename K, typename V>
LfuCache<K, V>::LfuCache(int capablity)
    : m_capablity(capablity){

      };

template <typename K, typename V>
LfuCache<K, V>::~LfuCache() {
    m_key_to_list_head.clear();
    m_freq_to_list.clear();
}

template <typename K, typename V>
void LfuCache<K, V>::Set(const K& key, const V& value) {
    if (m_key_to_list_head.find(key) != m_key_to_list_head.end()) {
        // key_to_list_head
        auto& node = m_key_to_list_head[key];
        int freq = node->m_freq;
        m_freq_to_list[freq].erase(node);
        if (m_freq_to_list[freq].size() == 0) {
            m_freq_to_list.erase(freq);
            if (freq == min_freq) ++min_freq;
        }
        Node const tmp(key, value, freq);
        freq++;
        m_freq_to_list[freq].push_front(tmp);
        m_key_to_list_head[key] = m_freq_to_list[freq].begin();

    } else {
        if (m_key_to_list_head.size() >= m_capablity) {
            m_key_to_list_head.erase(m_freq_to_list[min_freq].back().m_key);
            m_freq_to_list[min_freq].pop_back();

            if (m_freq_to_list[min_freq].size() == 0) {
                m_freq_to_list.erase(min_freq);
            }
        }
        Node const node{key, value, 1};
        m_freq_to_list[1].push_front(node);
        m_key_to_list_head[key] = m_freq_to_list[1].begin();
        min_freq = 1;
    }
}

template <typename K, typename V>
std::optional<V> LfuCache<K, V>::Get(const K& key) {
    if (m_key_to_list_head.find(key) != m_key_to_list_head.end()) {
        auto& n = m_key_to_list_head[key];
        V value = n->m_value;
        int freq = n->m_freq;

        m_freq_to_list[freq].erase(n);
        if (m_freq_to_list[freq].size() == 0) {
            m_freq_to_list.erase(freq);
            if (min_freq == freq) min_freq++;
        }
        freq++;
        m_freq_to_list[freq].push_front(Node(key, value, freq));
        m_key_to_list_head[key] = m_freq_to_list[freq].begin();

        return value;
    }
    return std::optional<V>();
}

TEST(lfu, t1) {
    LfuCache<int, int> lfu(2);
    lfu.Set(1, 1);
    lfu.Set(2, 2);
    lfu.Set(3, 3);
    auto ret = lfu.Get(1);
    EXPECT_EQ(!ret, true);

    ret = lfu.Get(2);
    EXPECT_EQ(ret, 2);

    ret = lfu.Get(3);
    EXPECT_EQ(ret, 3);
}
}  // namespace
