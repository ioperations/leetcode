/*Given an array of integers citations where citations[i] is the number of
citations a researcher received for their ith paper, return compute the
researcher's h-index.

According to the definition of h-index on Wikipedia: A scientist has an index h
if h of their n papers have at least h citations each, and the other n − h
papers have no more than h citations each.

If there are several possible values for h, the maximum one is taken as the
h-index.*/

#include <vector>
using namespace std;
#include <algorithm>

class Solution {
   public:
    int HIndex(vector<int>& citations) {
        // pass
        sort(citations.begin(), citations.end());
        int size = citations.size();
        int left = 0;
        int right = size - 1;

        while (left < right) {
            int middle = (left + right) / 2;
            while (middle < right) {
                if (citations[middle + 1] == citations[middle]) {
                    middle += 1;
                } else {
                    break;
                }
            }
        }
        return left;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> citations{3, 0, 6, 1, 5};
    int output = 3;
    Solution sl;
    int ret = sl.HIndex(citations);
    /*[3,0,6,1,5] means the researcher has 5 papers in total and each of them
    had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has
    3 papers with at least 3 citations each and the remaining two with no more
    than 3 citations each, their h-index is 3.*/
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<int> citations{1, 3, 1};
    int output = 1;
    Solution sl;
    int ret = sl.HIndex(citations);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
