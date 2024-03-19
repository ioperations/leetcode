// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/* Given a string s, reverse the order of characters in each word within a
   sentence while still preserving whitespace and initial word order.

*/

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stack>
#include <string>
#include <utility>

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
class Solution {
   public:
    string ReverseWordsV1(string s) {
        // TWO POINTER
        // O(1) SPACE
        // IN ONE PASS
        // O(N) TIME
        int current = 0;
        int left = 0;
        int right = 0;
        int const n = s.size();
        while (current < n) {
            while (right < n && s[right] != ' ') right++;
            current = right + 1;
            right--;
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            left = current;
            right = current;
        }
        return s;
    }
    string ReverseWords(string s) {
        // pass
        string ret;
        stack<char> stack;

        int const size = s.size();

        for (int i = 0; i < size; i++) {
            if (s[i] == ' ') {
                while (stack.size()) {
                    ret += stack.top();
                    stack.pop();
                }
                ret += " ";
                continue;
            }
            stack.push(s[i]);
        }
        while (stack.size()) {
            ret += stack.top();
            stack.pop();
        }

        return ret;
    }
};

TEST(reverse_words_in_a_string_iii, t1) {
    string const s = "Let's take LeetCode contest";
    string const output = "s'teL ekat edoCteeL tsetnoc";
    Solution sl;
    auto ret = sl.ReverseWords(s);
    EXPECT_EQ(ret, output);
}

TEST(reverse_words_in_a_string_iii, t2) {
    string const s = "God Ding";
    string const output = "doG gniD";
    Solution sl;
    auto ret = sl.ReverseWords(s);
    EXPECT_EQ(ret, output);
}

TEST(reverse_words_in_a_string_iii, bench) {
    string const s = "Let's take LeetCode contest";
    Solution sl;
    string const output = "s'teL ekat edoCteeL tsetnoc";

    BENCHMARK("BenchMarkStack") {
        auto ret = sl.ReverseWords(s);
        EXPECT_EQ(ret, output);
    };
}

TEST(reverse_words_in_a_string_iii, benchv2) {
    string const s = "Let's take LeetCode contest";
    Solution sl;
    string const output = "s'teL ekat edoCteeL tsetnoc";

    BENCHMARK("BenchMarkTwoPointer") {
        auto ret = sl.ReverseWordsV1(s);
        EXPECT_EQ(ret, output);
    };
}

}  // namespace
