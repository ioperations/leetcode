/*
 * Design a number container system that can do the following:
 *
 * Insert or Replace a number at the given index in the system.
 * Return the smallest index for the given number in the system.
 * Implement the NumberContainers class:
 *
 * NumberContainers() Initializes the number container system.
 * void change(int index, int number) Fills the container at index with the
 * number. If there is already a number at that index, replace it. int find(int
 * number) Returns the smallest index for the given number, or -1 if there is no
 * index that is filled by number in the system.
 *
 */

#include <algorithm>
#include <climits>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

class NumberContainers {
    /*
     * 1 <= index, number <= 109
     * At most 105 calls will be made in total to change and find.
     */
   public:
    NumberContainers() = default;

    void Change(int index, int number) {
        if (m_table.count(index) != 0) {
            auto n = m_table[index];
            auto& z = m_hm[n];
            z.erase(std::remove_if(z.begin(), z.end(),
                                   [&](auto i) { return (i == index); }),
                    z.end());
            if (z.empty()) {
                m_hm.erase(n);
            }
        }
        m_table[index] = number;
        m_hm[number].push_back(index);
    }

    int Find(int number) {
        auto it = m_hm.find(number);
        if (it != m_hm.end()) {
            int idx = std::numeric_limits<int>::max();
            auto& all = it->second;
            for (auto& ptr : all) {
                if (ptr < idx) {
                    idx = ptr;
                }
            }
            return idx;
        }
        return -1;
    }

   private:
    std::unordered_map<int, std::vector<int>> m_hm;
    std::unordered_map<int, int> m_table;
};

using namespace std;

class NumberContainersV2 {
    unordered_map<int, priority_queue<int, vector<int>, greater<>>> m_res;
    unordered_map<int, int> m_index_val;

   public:
    void Change(int index, int number) {
        if (m_index_val.count(index)) {
            int const prev_num = m_index_val[index];
            if (prev_num == number) return;
            m_res[prev_num].push(INT_MAX);  // Lazy deletion
        }
        m_res[number].push(index);
        m_index_val[index] = number;
    }

    int Find(int number) {
        while (!m_res[number].empty() &&
               m_index_val[m_res[number].top()] != number) {
            m_res[number].pop();
        }
        return m_res[number].empty() ? -1 : m_res[number].top();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

#include <gtest/gtest.h>

TEST(t0, t1) {
    // ["NumberContainers", "find", "change", "change", "change", "change",
    // "find", "change", "find"]
    // [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
    NumberContainers sl;
    auto ret = sl.Find(10);
    EXPECT_EQ(ret, -1);

    sl.Change(2, 10);
    sl.Change(1, 10);
    sl.Change(3, 10);
    sl.Change(5, 10);
    ret = sl.Find(10);
    EXPECT_EQ(ret, 1);

    sl.Change(1, 20);
    ret = sl.Find(10);
    EXPECT_EQ(ret, 2);
    // Output
    // [null, -1, null, null, null, null, 1, null, 2]
    /*
     Explanation
     NumberContainers nc = new NumberContainers();
     nc.find(10); // There is no index that is filled with number 10. Therefore,
     we return -1.

     nc.change(2, 10); // Your container at index 2 will be filled
     with number 10.

     nc.change(1, 10); // Your container at index 1 will be filled with
     number 10.

     nc.change(3, 10); // Your container at index 3 will be filled with
     number 10.

     nc.change(5, 10); // Your container at index 5 will be filled with
     number 10.

     nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5. Since the
     smallest index that is filled with 10 is 1, we return 1.

     nc.change(1, 20); // Your container at index 1 will be filled with
     number 20. Note that index 1 was filled with 10 and then replaced with 20.

     -> nc.find(10); // Number 10 is at the indices 2, 3, and 5. The smallest
     index that is filled with 10 is 2. Therefore, we return 2.
    */
}

TEST(t1, t1) {
    // ["NumberContainers", "find", "change", "change", "change", "change",
    // "find", "change", "find"]
    // [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
    NumberContainersV2 sl;
    auto ret = sl.Find(10);
    EXPECT_EQ(ret, -1);

    sl.Change(2, 10);
    sl.Change(1, 10);
    sl.Change(3, 10);
    sl.Change(5, 10);
    ret = sl.Find(10);
    EXPECT_EQ(ret, 1);

    sl.Change(1, 20);
    ret = sl.Find(10);
    EXPECT_EQ(ret, 2);
    // Output
    // [null, -1, null, null, null, null, 1, null, 2]
    /*
     Explanation
     NumberContainers nc = new NumberContainers();
     nc.find(10); // There is no index that is filled with number 10. Therefore,
     we return -1.

     nc.change(2, 10); // Your container at index 2 will be filled
     with number 10.

     nc.change(1, 10); // Your container at index 1 will be filled with
     number 10.

     nc.change(3, 10); // Your container at index 3 will be filled with
     number 10.

     nc.change(5, 10); // Your container at index 5 will be filled with
     number 10.

     nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5. Since the
     smallest index that is filled with 10 is 1, we return 1.

     nc.change(1, 20); // Your container at index 1 will be filled with
     number 20. Note that index 1 was filled with 10 and then replaced with 20.

     -> nc.find(10); // Number 10 is at the indices 2, 3, and 5. The smallest
     index that is filled with 10 is 2. Therefore, we return 2.
    */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
