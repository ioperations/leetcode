// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <string>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    Solution(){};
    virtual ~Solution(){};
    bool IsPalindrome(int x) {
        return std::to_string(x) == Reverse(std::to_string(x));
    }

   private:
    static std::string Reverse(const std::string &s) {
        if (s.size() <= 1) {
            return s;
        }

        return Reverse(s.substr(1)) + s[0];
    }
};

TEST(palindrom_number, t1) {
    Solution s;

    bool ret = s.IsPalindrome(121);
    EXPECT_EQ(ret, true);
}

TEST(palindrom_number, t2) {
    Solution s;

    const bool ret = s.IsPalindrome(-121);
    EXPECT_EQ(ret, false);
}

TEST(palindrom_number, t3) {
    Solution s;

    const bool ret = s.IsPalindrome(10);

    EXPECT_EQ(ret, false);
}
}  // namespace
