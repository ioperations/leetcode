// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <string>

#include "gtest/gtest.h"


namespace { 
class Solution {
   public:
    int RomanToInt(std::string s) {
        int i = 0;
        int sum = 0;
        int len = s.length();
        int current, next;

        for (i = 0; i < len; i++) {
            current = Basic(s[i]);
            if (i == len - 1)  // last element
            {
                sum += current;
                break;
            }
            next = Basic(s[i + 1]);
            //  cout << "current = " << current << " next = " << next << endl;

            if (current > next) {
                sum += current;
            } else if (current == next) {
                sum += current;
            } else  // left smaller than right:
            {
                sum += (next - current);
                i++;
            }
        }
        return sum;
    }

    int Basic(char c) {
        switch (c) {
            case 'I':
                return 1;
                break;
            case 'V':
                return 5;
                break;
            case 'X':
                return 10;
                break;
            case 'L':
                return 50;
                break;
            case 'C':
                return 100;
                break;
            case 'D':
                return 500;
                break;
            case 'M':
                return 1000;
                break;
            default:
                return 0;
                break;
        }
    }
};


TEST(t0, t1) {
    Solution s;

    std::string input = "III";
    int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 3);
}

TEST(t0, t2) {
    Solution s;
    std::string input = "LVIII";
    int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 58);
}

TEST(t0, t3) {
    Solution s;
    std::string input = "MCMXCIV";
    int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 1994);
}

}
