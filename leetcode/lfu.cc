
#include <list>
#include <optional>
#include <unordered_map>

template <typename K, typename V>
class LfuCache {
   public:
    LfuCache(int capablity);
    LfuCache(LfuCache &&) = default;
    LfuCache(const LfuCache &) = default;
    ~LfuCache();
    void Set(const K &key, const V &value);
    std::optional<V> Get(const K &key);

   private:
    struct Node {
        K key;
        V value;
        int freq;
        Node(K key, V value, int freq) : key(key), value(value), freq(freq) {}
    };
    int min_freq;
    int m_capablity;
    std::unordered_map<K, typename std::list<Node>::iterator> key_to_list_head;
    std::unordered_map<int, typename std::list<Node>> freq_to_list;
};

template <typename K, typename V>
LfuCache<K, V>::LfuCache(int capablity) {
    m_capablity = capablity;
    min_freq = 1;
};

template <typename K, typename V>
LfuCache<K, V>::~LfuCache() {
    key_to_list_head.clear();
    freq_to_list.clear();
}

template <typename K, typename V>
void LfuCache<K, V>::Set(const K &key, const V &value) {
    if (key_to_list_head.find(key) != key_to_list_head.end()) {
        // key_to_list_head
        auto node = key_to_list_head[key];
        int freq = node->freq;
        freq_to_list[freq].erase(node);
        if (freq_to_list[freq].size() == 0) {
            freq_to_list.erase(freq);
            if (freq == min_freq) ++min_freq;
        }
        freq_to_list[++freq].push_front(Node(key, value, freq));
        key_to_list_head[key] = freq_to_list[freq].begin();

    } else {
        if (key_to_list_head.size() >= m_capablity) {
            key_to_list_head.erase(freq_to_list[min_freq].back().key);
            freq_to_list[min_freq].pop_back();

            if (freq_to_list[min_freq].size() == 0) {
                freq_to_list.erase(min_freq);
            }
        }
        Node node{key, value, 1};
        freq_to_list[1].push_front(node);
        key_to_list_head[key] = freq_to_list[1].begin();
        min_freq = 1;
    }
}

template <typename K, typename V>
std::optional<V> LfuCache<K, V>::Get(const K &key) {
    if (key_to_list_head.find(key) != key_to_list_head.end()) {
        auto n = key_to_list_head[key];
        V value = n->value;
        int freq = n->freq;

        freq_to_list[freq].erase(n);
        if (freq_to_list[freq].size() == 0) {
            freq_to_list.erase(freq);
            if (min_freq == freq) min_freq++;
        }
        freq++;
        freq_to_list[freq].push_front(Node(key, value, freq));
        key_to_list_head[key] = freq_to_list[freq].begin();

        return value;
    }
    return std::optional<V>();
}

#include <gtest/gtest.h>

TEST(t0, t1) {
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

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
