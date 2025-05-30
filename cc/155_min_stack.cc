

#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class MinStack {
   public:
    vector<pair<int, int>> m_v;
    MinStack() {
        // do nothing
    }

    void Push(int val) {
        // 1st element
        if (m_v.size() == 0) {
            m_v.emplace_back(val, val);
        } else {
            // check min element of last pair
            pair<int, int> const prev = m_v.back();

            int const mini = min(val, prev.second);
            m_v.emplace_back(val, mini);
        }
    }

    void Pop() { m_v.pop_back(); }

    int Top() { return m_v.back().first; }

    int GetMin() { return m_v.back().second; }
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
