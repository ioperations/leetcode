// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Design a class to find the kth largest element in a stream. Note that it is
the kth largest element in the sorted order, not the kth distinct element.

Implement KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer k and the
stream of integers nums. int add(int val) Appends the integer val to the stream
and returns the element representing the kth largest element in the stream.*/

#include <functional>
#include <queue>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> q;
    int k;

   public:
    KthLargest(int k, vector<int> &nums) : k(k) {
        int size = nums.size();
        for (int i = 0; i < size; i++) {
            q.push(nums[i]);
            if ((int)q.size() > k) q.pop();
        }
    }

    int Add(int val) {
        q.push(val);
        if ((int)q.size() > k) {
            q.pop();
        }

        return q.top();
    }
};

TEST(kth_largest_element_in_a_stream, t1) {
    // * Your KthLargest object will be instantiated and called as such:
    int k = 3;
    std::vector<int> nums{4, 5, 8, 2};
    KthLargest *obj = new KthLargest(k, nums);
    int ret = 0;
    ret = obj->Add(3);  // return 4
    EXPECT_EQ(ret, 4);
    ret = obj->Add(5);  // return 5
    EXPECT_EQ(ret, 5);
    ret = obj->Add(10);  // return 5
    EXPECT_EQ(ret, 5);
    ret = obj->Add(9);  // return 8
    EXPECT_EQ(ret, 8);
    ret = obj->Add(4);  // return 8
    EXPECT_EQ(ret, 8);
    delete obj;
}

}  // namespace
