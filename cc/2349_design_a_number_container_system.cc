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
    NumberContainers() {}

    void change(int index, int number) {
        if (table.count(index) != 0) {
            auto n = table[index];
            auto &z = hm[n];
            z.erase(std::remove_if(z.begin(), z.end(),
                                   [&](auto i) { return (i == index); }),
                    z.end());
            if (z.empty()) {
                hm.erase(n);
            }
        }
        table[index] = number;
        hm[number].push_back(index);
    }

    int find(int number) {
        auto it = hm.find(number);
        if (it != hm.end()) {
            int idx = std::numeric_limits<int>::max();
            auto &all = it->second;
            for (auto &ptr : all) {
                if (ptr < idx) {
                    idx = ptr;
                }
            }
            return idx;
        }
        return -1;
    }

   private:
    std::unordered_map<int, std::vector<int>> hm;
    std::unordered_map<int, int> table;
};

using namespace std;

class NumberContainersV2 {
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> res;
    unordered_map<int, int> index_val;

   public:
    void change(int index, int number) {
        if (index_val.count(index)) {
            int prevNum = index_val[index];
            if (prevNum == number) return;
            res[prevNum].push(INT_MAX);  // Lazy deletion
        }
        res[number].push(index);
        index_val[index] = number;
    }

    int find(int number) {
        while (!res[number].empty() && index_val[res[number].top()] != number) {
            res[number].pop();
        }
        return res[number].empty() ? -1 : res[number].top();
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
    auto ret = sl.find(10);
    EXPECT_EQ(ret, -1);

    sl.change(2, 10);
    sl.change(1, 10);
    sl.change(3, 10);
    sl.change(5, 10);
    ret = sl.find(10);
    EXPECT_EQ(ret, 1);

    sl.change(1, 20);
    ret = sl.find(10);
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
    auto ret = sl.find(10);
    EXPECT_EQ(ret, -1);

    sl.change(2, 10);
    sl.change(1, 10);
    sl.change(3, 10);
    sl.change(5, 10);
    ret = sl.find(10);
    EXPECT_EQ(ret, 1);

    sl.change(1, 20);
    ret = sl.find(10);
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

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
