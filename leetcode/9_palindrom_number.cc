// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <string>

namespace { 
class Sulution {
   public:
    Sulution(){};
    virtual ~Sulution(){};
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
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    Sulution s;

    bool ret = s.IsPalindrome(121);
    EXPECT_EQ(ret, true);
}

TEST(t0, t2) {
    Sulution s;

    bool ret = s.IsPalindrome(-121);
    EXPECT_EQ(ret, false);
}

TEST(t0, t3) {
    Sulution s;

    bool ret = s.IsPalindrome(10);
    EXPECT_EQ(ret, false);
}
}
