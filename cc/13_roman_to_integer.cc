// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <string>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int RomanToInt(const std::string& s) const {
        int i = 0;
        int sum = 0;
        int const len = static_cast<int>(s.length());
        int current = 0, next = 0;

        for (i = 0; i < len; i++) {
            current = Basic(s.at(i));
            if (i == len - 1)  // last element
            {
                sum += current;
                break;
            }
            next = Basic(s.at(i + 1));
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

    int Basic(char c) const {
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

TEST(RomanToInteger, t1) {
    Solution const s;

    const std::string input = "III";
    const int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 3);
}

TEST(RomanToInteger, t2) {
    Solution const s;
    const std::string input = "LVIII";
    const int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 58);
}

TEST(RomanToInteger, t3) {
    Solution const s;
    const std::string input = "MCMXCIV";
    const int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 1994);
}

}  // namespace
