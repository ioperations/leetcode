/*
 *Given an array of strings nums containing n unique binary strings each of
 length n, return a binary string of length n that does not appear in nums. If
 there are multiple answers, you may return any of them.


 * */

#include <set>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string FindDifferentBinaryString(vector<string>& nums) {
      /* n == nums.length
       1 <= n <= 16
       nums[i].length == n
       nums[i] is either '0' or '1'.
       All the strings of nums are unique.
      */

      auto n = nums.size();

      set<long long> s;
      Get(nums, s);

      long long v = 0;

      string str(n, '0');
      Gen(str, v, 0, n, s);
      return str;
    }

    bool Gen(string& str, long long& v, int index, int n,
             const std::set<long long>& s) {
        if (index == n) {
            if (s.count(v) == 0) {
                return true;
            }
            return false;
        }

        for (int i = 0; i < 2; i++) {
            v = v * 10 + i;
            str[index] = '0' + i;

            if (Gen(str, v, index + 1, n, s)) {
                return true;
            }
            v = v / 10;
        }
        return false;
    }

    void Get(vector<string>& ori, set<long long>& s) {
      for (const auto& value : ori) {
        s.emplace(GetInt(value));
      }
    }

    long long GetInt(const std::string& v) {
      long long ret = 0;
      for (auto chars : v) {
        ret = ret * 10 + (chars - '0');
      }
      return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<string> nums = {"01", "10"};
    set<string> const set = {"11", "00"};
    // Explanation: "11" does not appear in nums. "00" would also be correct.
    Solution sl;
    auto ret = sl.FindDifferentBinaryString(nums);
    EXPECT_TRUE(set.count(ret) > 0);
}

TEST(t0, t2) {
    vector<string> nums = {"00", "01"};
    set<string> const set = {"11", "10"};
    // Explanation: "11" does not appear in nums. "00" would also be correct.
    // "11" does not appear in nums. "10" would also be correct.

    Solution sl;
    auto ret = sl.FindDifferentBinaryString(nums);
    EXPECT_TRUE(set.count(ret) > 0);
}

TEST(t0, t3) {
    vector<string> nums = {"111", "011", "001"};
    set<string> const set = {"101", "000", "010", "100", "110"};
    // Explanation: "101" does not appear in nums. "000", "010", "100", and
    // "110" would also be correct.

    Solution sl;
    auto ret = sl.FindDifferentBinaryString(nums);
    EXPECT_TRUE(set.count(ret) > 0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
