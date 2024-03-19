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
#include <stddef.h>

#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <stack>
#include <string>
#include <vector>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class NestedInteger {
    bool is_integer = true;
    int val;
    vector<NestedInteger> vec;

   public:
    // Constructor initializes an empty nested list.
    NestedInteger() {}

    // Constructor initializes a single integer.
    NestedInteger(int value) {
        is_integer = true;
        val = value;
    }

    // Return true if this NestedInteger holds a single integer, rather than a
    // nested list.
    bool IsInteger() const { return is_integer; }

    // Return the single integer that this NestedInteger holds, if it holds a
    // single integer The result is undefined if this NestedInteger holds a
    // nested list
    int GetInteger() const { return val; }

    // Set this NestedInteger to hold a single integer.
    void SetInteger(int value) {
        vec.clear();
        val = value;
        is_integer = true;
    }

    // Set this NestedInteger to hold a nested list and adds a nested integer to
    // it.
    void Add(const NestedInteger &ni) {
        vec.push_back(ni);
        is_integer = false;
    }

    // Return the nested list that this NestedInteger holds, if it holds a
    // nested list The result is undefined if this NestedInteger holds a single
    // integer
    const vector<NestedInteger> &GetList() const { return vec; }
};
class Solution {
   public:
    NestedInteger Deserialize(std::string s) {
        const function<bool(char)> isnumber = [](char c) {
            return (c == '-') || isdigit(c);
        };

        stack<NestedInteger> stk;
        stk.push(NestedInteger());

        for (auto it = s.begin(); it != s.end();) {
            const char &c = (*it);
            if (isnumber(c)) {
                auto it2 = find_if_not(it, s.end(), isnumber);
                const int val = stoi(string(it, it2));
                stk.top().Add(NestedInteger(val));
                it = it2;
            } else {
                if (c == '[') {
                    stk.push(NestedInteger());
                } else if (c == ']') {
                    const NestedInteger ni = stk.top();
                    stk.pop();
                    stk.top().Add(ni);
                }
                ++it;
            }
        }

        NestedInteger result = stk.top().GetList().front();
        return result;
    }

    NestedInteger DeserializeV1(string s) {
        stack<NestedInteger> stk({NestedInteger()});
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '[') {
                stk.push(NestedInteger());
            } else if (s[i] == ']') {
                const NestedInteger ni = stk.top();
                stk.pop();
                stk.top().Add(ni);
            } else if (s[i] == ',') {
            } else {
                int v = 0;
                bool negative = false;
                if (s[i] == '-') {
                    negative = true;
                    ++i;
                }
                for (; i < s.size() && '0' <= s[i] && s[i] <= '9'; ++i) {
                    v = v * 10 + s[i] - '0';
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

void Flattern(const NestedInteger &n, vector<int> &ret) {
    if (!n.IsInteger()) {
        for (auto &ptr : n.GetList()) {
            Flattern(ptr, ret);
        }
    } else {
        ret.push_back(n.GetInteger());
    }
}

TEST(base, mini_parser_385) {
    const NestedInteger tmp(1);

    vector<int> vec;

    Flattern(tmp, vec);

    EXPECT_EQ(vec, vector<int>{1});
}

TEST(mini_parser, t1) {
    const string s = "324";
    // Explanation: You should return a NestedInteger object which contains
    // a single integer 324.

    Solution sl;
    auto ret = sl.Deserialize(s);
    EXPECT_EQ(ret.IsInteger(), true);

    EXPECT_EQ(ret.GetInteger(), 324);

    ret = sl.DeserializeV1(s);

    vector<int> vec;
    Flattern(ret, vec);

    EXPECT_EQ(vec, (std::vector<int>{324}));
}

TEST(mini_parser, t2) {
    const string s = "[123,[456,[789]]]";
    // Output: [123,[456,[789]]]
    // Explanation: Return a NestedInteger object containing a nested list
    // with 2 elements:
    // 1. An integer containing value 123.
    // 2. A nested list containing two elements:
    //     i.  An integer containing value 456.
    //     ii. A nested list with one element:
    //          a. An integer containing value 789

    Solution sl;
    // Output: [123,[456,[789]]]
    auto ret = sl.Deserialize(s);

    vector<int> vec;
    Flattern(ret, vec);

    EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
    auto ret1 = sl.DeserializeV1(s);

    vec.clear();
    Flattern(ret, vec);

    EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
}

TEST(Deserialize, t1) {
    const string s = "[123,[456,[789]]]";
    // Output: [123,[456,[789]]]
    // Explanation: Return a NestedInteger object containing a nested list
    // with 2 elements:
    // 1. An integer containing value 123.
    // 2. A nested list containing two elements:
    //     i.  An integer containing value 456.
    //     ii. A nested list with one element:
    //          a. An integer containing value 789

    BENCHMARK("Deserialize") {
        Solution sl;
        // Output: [123,[456,[789]]]
        auto ret = sl.Deserialize(s);

        vector<int> vec;
        Flattern(ret, vec);

        EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
    };
}

TEST(DeserializeV1, t1) {
    const string s = "[123,[456,[789]]]";
    // Output: [123,[456,[789]]]
    // Explanation: Return a NestedInteger object containing a nested list
    // with 2 elements:
    // 1. An integer containing value 123.
    // 2. A nested list containing two elements:
    //     i.  An integer containing value 456.
    //     ii. A nested list with one element:
    //          a. An integer containing value 789

    BENCHMARK("BenchV2") {
        Solution sl;
        // Output: [123,[456,[789]]]
        auto ret = sl.DeserializeV1(s);

        vector<int> vec;
        Flattern(ret, vec);

        EXPECT_EQ(vec, (std::vector<int>{123, 456, 789}));
    };
}

}  // namespace
