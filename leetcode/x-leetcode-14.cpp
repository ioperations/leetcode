#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string LongestCommonPrefix(vector<string>& strs) {
        string s = "";

        int j = 0;
        char tocompare = ' ';
        while (true) {
            for (int i = 0; i < strs.size(); ++i) {
                if ((j < strs[i].length())) {
                    if (i == 0) {
                        tocompare = strs[i][j];
                    }
                    if (strs[i][j] != tocompare) {
                        return s;
                    }
                } else {
                    return s;
                }
            }
            s += tocompare;
            j++;
        }
        return s;
    }
};

#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <iostream>

TEST(main, r1) {
    Solution s;
    vector<string> input{"flight", "flow", "flight"};
    string str = s.LongestCommonPrefix(input);
    EXPECT_EQ(str, "fl");
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
