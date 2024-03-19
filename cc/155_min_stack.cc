

#include <algorithm>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class MinStack {
   public:
    vector<pair<int, int>> v;
    MinStack() {
        // do nothing
    }

    void Push(int val) {
        // 1st element
        if (v.size() == 0) {
            pair<int, int> p;
            p.first = val;
            p.second = val;
            v.push_back(p);
        }

        else {
            // check min element of last pair
            pair<int, int> prev = v.back();

            int mini = min(val, prev.second);
            pair<int, int> p;
            p.first = val;
            p.second = mini;
            v.push_back(p);
        }
    }

    void Pop() { v.pop_back(); }

    int Top() {
        pair<int, int> p = v.back();
        return p.first;
    }

    int GetMin() {
        pair<int, int> p = v.back();
        return p.second;
    }
};

TEST(min_stack, t1) {
    MinStack min_stack;
    min_stack.Push(-2);
    min_stack.Push(0);
    min_stack.Push(-3);
    int ret = min_stack.GetMin();  // return -3
    EXPECT_EQ(ret, -3);
    min_stack.Pop();
    ret = min_stack.Top();  // return 0
    EXPECT_EQ(ret, 0);
    ret = min_stack.GetMin();  // return -2
    EXPECT_EQ(ret, -2);
}

}  // namespace
