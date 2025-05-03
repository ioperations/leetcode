/*
 * Construct the Lexicographically Largest Valid Sequence
 * Given an integer n, find a sequence that satisfies all of the following:
 * The integer 1 occurs once in the sequence.
 * Each integer between 2 and n occurs twice in the sequence.
 * For every integer i between 2 and n, the distance between the two occurrences
 * of i is exactly i. The distance between two numbers on the sequence, a[i] and
 * a[j], is the absolute difference of their indices, |j - i|.
 *
 * Return the lexicographically largest sequence. It is guaranteed that under
 * the given constraints, there is always a solution.
 *
 * A sequence a is lexicographically larger than a sequence b (of the same
 * length) if in the first position where a and b differ, sequence a has a
 * number greater than the corresponding number in b. For example, [0,1,9,0] is
 * lexicographically larger than [0,1,5,6] because the first position they
 * differ is at the third number, and 9 is greater than 5.
 *
 */

#include <cstddef>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> ConstructDistancedSequence(int n) {
      const int num = 2 * n - 1;
      vector<int> results(num, 0);
      vector<int> value_set;
      vector<bool> exists(n - 1, true);
      for (int i = n; i > 1; i--) {
        value_set.push_back(i);
      }

      Gen(results, value_set, exists, false);
      return results;
    }

    // 贪婪算法:
    // 从最大的数开始填充，如果填充不了，就回溯到上一个数，尝试填充下一个数
    // 递归的方式，填充到最后一个数，如果填充成功，就返回true，否则返回false
    // 如果前面的填充不了，就填充1，就标记numberOneUsed为true，表示1已经被使用过了
    bool Gen(vector<int>& results, const vector<int>& value_set,
             vector<bool>& exists, bool number_one_used, int index = 0,
             int fillsize = 0) {
      // 复杂度为O(n!)
      auto result_size = results.size();
      if (fillsize == result_size) {
        return true;
      }

      if (results[index] != 0) {
        return Gen(results, value_set, exists, number_one_used, index + 1,
                   fillsize);
      }

      for (size_t i = 0; i < value_set.size(); i++) {
        if (!exists[i]) {
          continue;
        }

        const auto value = value_set[i];
        if (index + value >= result_size || results[index + value] != 0) {
          continue;
        }

        results[index] = value;
        results[index + value] = value;
        exists[i] = false;

        if (Gen(results, value_set, exists, number_one_used, index + 1,
                fillsize + 2)) {
          return true;
        }

        results[index] = 0;
        results[index + value] = 0;
        exists[i] = true;
      }
      if (number_one_used) {
        return false;
      }

      results[index] = 1;
      if (Gen(results, value_set, exists, true, index + 1, fillsize + 1)) {
        return true;
      }
      results[index] = 0;
      return false;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
  int const n = 3;
  std::vector<int> const output = {3, 1, 2, 3, 2};
  // Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the
  // lexicographically largest valid sequence.

  Solution sl;
  auto ret = sl.ConstructDistancedSequence(n);
  EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
  int const n = 5;
  std::vector<int> const output = {5, 3, 1, 4, 3, 5, 2, 4, 2};
  // Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the
  // lexicographically largest valid sequence.

  Solution sl;
  auto ret = sl.ConstructDistancedSequence(n);
  EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
  int const n = 6;
  std::vector<int> const output = {6, 4, 2, 5, 2, 4, 6, 3, 5, 1, 3};

  Solution sl;
  auto ret = sl.ConstructDistancedSequence(n);
  EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
