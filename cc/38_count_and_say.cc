// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <string>

#include "gtest/gtest.h"

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    std::string CountAndSay(int n) {
        std::string ret = "1";
        for (int i = 0; i < (n - 1); i++) {
            CountAndSay(ret);
        }
        return ret;
    }

    void CountAndSay(std::string &s) {
        // pass

        char last = '0';
        int count = 0;
        bool set = false;

        std::string tmp = "";
        for (const auto &ptr : s) {
            if (!set) {
                last = ptr;
                set = true;
                count = 1;
            } else {
                if (last == ptr) {
                    count++;
                } else {
                    tmp += '0' + count;
                    tmp += last;

                    last = ptr;
                    count = 1;
                }
            }
        }

        if (count) {
            tmp += '0' + count;
            tmp += last;
        }

        s = tmp;
    }
};



TEST(t0, t1) {
    int n = 4;
    std::string output = "1211";
    Solution s;
    auto ret = s.CountAndSay(n);

    EXPECT_EQ(ret, output);
    // countAndSay(1) = "1"
    // countAndSay(2) = say "1" = one 1 = "11"
    // countAndSay(3) = say "11" = two 1's = "21"
    // countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"
}

TEST(t0, t2) {
    int n = 1;
    std::string output = "1";
    Solution s;
    auto ret = s.CountAndSay(n);

    EXPECT_EQ(ret, output);
    // Explanation : This is the base case.
}
}
