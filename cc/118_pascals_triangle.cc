// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above
it as shown:
*/


#include <vector>
using namespace std;

namespace { 
class Solution {
   public:
    vector<vector<int>> Generate(int num_rows) {
        // 1 <= num_rows <= 30
        vector<vector<int>> ret;
        ret.push_back({1});

        while (num_rows != 1) {
            num_rows--;

            auto r = ret.back();
            r.push_back(0);

            vector<int> next;
            for (int i = 0; i < (int)r.size(); i++)
                next.push_back((i == 0 ? 0 : r[i - 1]) + r[i]);

            r.pop_back();
            ret.push_back(next);
        }

        return ret;
    }
};

#include <set>

TEST(t0, t1) {
    int num_rows = 5;
    std::vector<std::vector<int>> output = {
        {1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};

    std::set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.Generate(num_rows);
    std::set<vector<int>> ret_set(ret.begin(), ret.end());

    EXPECT_EQ(ret_set, output_set);
}

TEST(t0, t2) {
    int num_rows = 1;
    std::vector<std::vector<int>> output = {{1}};

    std::set<vector<int>> output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.Generate(num_rows);
    std::set<vector<int>> ret_set(ret.begin(), ret.end());

    EXPECT_EQ(ret_set, output_set);
}

}
