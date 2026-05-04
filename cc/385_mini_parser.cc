// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string s represents the serialization of a nested list, implement a
parser to deserialize it and return the deserialized NestedInteger.

Each element is either an integer or a list whose elements may also be integers
or other lists.
*/

// // This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
#include <benchmark/benchmark.h>

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <functional>
#include <stack>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace {
class NestedInteger {
   private:
    bool m_is_integer = true;
    int m_val{};
    std::vector<NestedInteger> m_vec;

   public:
    // Constructor initializes an empty nested list.
    NestedInteger() = default;

    // Constructor initializes a single integer.
    NestedInteger(int value) : m_val(value) {}

    // Return true if this NestedInteger holds a single integer, rather than a
    // nested list.
    [[nodiscard]] bool IsInteger() const { return m_is_integer; }

    // Return the single integer that this NestedInteger holds, if it holds a
    // single integer The result is undefined if this NestedInteger holds a
    // nested list
    [[nodiscard]] int GetInteger() const { return m_val; }

    // Set this NestedInteger to hold a single integer.
    void SetInteger(int value) {
        m_vec.clear();
        m_val = value;
        m_is_integer = true;
    }

    // Set this NestedInteger to hold a nested list and adds a nested integer to
    // it.
    void Add(const NestedInteger& ni) {
        m_vec.emplace_back(ni);
        m_is_integer = false;
    }

    // Return the nested list that this NestedInteger holds, if it holds a
    // nested list The result is undefined if this NestedInteger holds a single
    // integer
    [[nodiscard]] const std::vector<NestedInteger>& GetList() const { return m_vec; }
};
class Solution {
   public:
    [[nodiscard]]
    NestedInteger Deserialize(std::string s) const {
        const std::function<bool(char)> isnumber = [](char c) {
            return (c == '-') || std::isdigit(c);
        };

        std::stack<NestedInteger> stk;
        stk.emplace();

        for (auto it = s.begin(); it != s.end();) {
            const char& c = (*it);
            if (isnumber(c)) {
                auto it2 = std::find_if_not(it, s.end(), isnumber);
                const int val = std::stoi(std::string(it, it2));
                stk.top().Add(NestedInteger(val));
                it = it2;
            } else {
                if (c == '[') {
                    stk.emplace();
                } else if (c == ']') {
                    const NestedInteger ni = stk.top();
                    stk.pop();
                    stk.top().Add(ni);
                }
                ++it;
            }
        }

        return stk.top().GetList().front();
    }

    [[nodiscard]]
    NestedInteger DeserializeV1(std::string s) const {
        constexpr int k_base = 10;
        std::stack<NestedInteger> stk({NestedInteger()});
        for (size_t i = 0; i < s.size(); ++i) {
            if (s.at(i) == '[') {
                stk.emplace();
            } else if (s.at(i) == ']') {
                const NestedInteger ni = stk.top();
                stk.pop();
                stk.top().Add(ni);
            } else if (s.at(i) == ',') {
            } else {
                int v = 0;
                bool negative = false;
                if (s.at(i) == '-') {
                    negative = true;
                    ++i;
                }
                for (; i < s.size() && '0' <= s.at(i) && s.at(i) <= '9'; ++i) {
                    v = v * k_base + s.at(i) - '0';
                }
                if (negative) {
                    v = -v;
                }
                --i;

                stk.top().Add(NestedInteger(v));
            }
        }

        return stk.top().GetList().front();
    }
};

void Flattern(const NestedInteger& n, std::vector<int>& ret) {
    if (!n.IsInteger()) {
        for (auto& ptr : n.GetList()) {
            Flattern(ptr, ret);
        }
    } else {
        ret.push_back(n.GetInteger());
    }
}

TEST(Base, t0) {
    const NestedInteger tmp(1);

    std::vector<int> vec;

    Flattern(tmp, vec);

    EXPECT_EQ(vec, std::vector<int>{1});
}

TEST(miniV, t1) {
    const std::string s = "324";
    // Explanation: You should return a NestedInteger object which contains
    // a single integer 324.

    Solution const sl;
    auto ret = sl.Deserialize(s);
    EXPECT_EQ(ret.IsInteger(), true);

    EXPECT_EQ(ret.GetInteger(), 324);

    ret = sl.DeserializeV1(s);

    std::vector<int> vec;
    Flattern(ret, vec);

    EXPECT_EQ(vec, (std::vector<int>{324}));
}

TEST(miniV, t2) {
    const std::string s = "[123,[456,[789]]]";
    // Output: [123,[456,[789]]]
    // Explanation: Return a NestedInteger object containing a nested list
    // with 2 elements:
    // 1. An integer containing value 123.
    // 2. A nested list containing two elements:
    //     i.  An integer containing value 456.
    //     ii. A nested list with one element:
    //          a. An integer containing value 789

    Solution const sl;
    // Output: [123,[456,[789]]]
    auto ret = sl.Deserialize(s);

    std::vector<int> vec;
    Flattern(ret, vec);

    EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
    auto ret1 = sl.DeserializeV1(s);

    vec.clear();
    Flattern(ret, vec);

    EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
}

void BenchV1(benchmark::State& state) {
    for (auto&& _ : state) {
        const std::string s = "[123,[456,[789]]]";
        // Output: [123,[456,[789]]]
        // Explanation: Return a NestedInteger object containing a nested list
        // with 2 elements:
        // 1. An integer containing value 123.
        // 2. A nested list containing two elements:
        //     i.  An integer containing value 456.
        //     ii. A nested list with one element:
        //          a. An integer containing value 789

        Solution const sl;
        // Output: [123,[456,[789]]]
        auto ret = sl.Deserialize(s);

        std::vector<int> vec;
        Flattern(ret, vec);

        EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
    }
}
BENCHMARK(BenchV1);

void BenchV2(benchmark::State& state) {
    for (auto&& _ : state) {
        const std::string s = "[123,[456,[789]]]";
        // Output: [123,[456,[789]]]
        // Explanation: Return a NestedInteger object containing a nested list
        // with 2 elements:
        // 1. An integer containing value 123.
        // 2. A nested list containing two elements:
        //     i.  An integer containing value 456.
        //     ii. A nested list with one element:
        //          a. An integer containing value 789

        Solution const sl;
        // Output: [123,[456,[789]]]
        auto ret = sl.DeserializeV1(s);

        std::vector<int> vec;
        Flattern(ret, vec);

        EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
    }
}
BENCHMARK(BenchV2);

}  // namespace
