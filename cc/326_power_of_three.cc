// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer n, return true if it is a power of three.Otherwise,
    return false.

    An integer n is a power of three,
    if there exists an integer x such that n == 3x.
*/

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    bool IsPowerOfThree(int n) {
        if (n == 0) {
            return false;
        }
        if (n % 3 == 0) {
            return true;
        }
        return false;
    }
};

TEST(power_of_three, t1) {
  int const n = 27;
  bool const expected = true;

  Solution sl;
  bool const ret = sl.IsPowerOfThree(n);
  EXPECT_EQ(ret, expected);
}

TEST(power_of_three, t2) {
  int const n = 0;
  bool const expected = false;

  Solution sl;
  bool const ret = sl.IsPowerOfThree(n);
  EXPECT_EQ(ret, expected);
}
TEST(power_of_three, t3) {
  int const n = 9;
  bool const expected = true;

  Solution sl;
  bool const ret = sl.IsPowerOfThree(n);
  EXPECT_EQ(ret, expected);
}

}  // namespace
