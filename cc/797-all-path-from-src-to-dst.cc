// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <ctime>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

/// find add the paths from source to destnation
/// 0 -> graph.size()-1
/// graph is a dag (directed acyclic graph)
namespace {
class Solution {
   public:
    vector<vector<int>> AllPathsSourceTarget(vector<vector<int>>& graph) {
        clock_t start = 0, end = 0;
        start = clock();

        auto tmp = ImplV1(graph);
        end = clock();
        std::cout << "impl_v1 cost time " << end - start << std::endl;

        return tmp;
    }

   private:
    /// 先找最后一级前面相连的一级，用栈存储，
    /// pop出来一个 ，以当前接待你继续向前找，并用栈存储
    /// 所有的路径都找完 找到第一个
    /// 根dfs还不一样 还要找到所有的路径 ， 不能只有一个stack
    vector<vector<int>> ImplV1(vector<vector<int>>& graph) { return {{}}; }
};

TEST(_all_path_from_src_to_dstv2, t2) {
    Solution const n;

    (void)n;
    EXPECT_EQ(0, 0 + 0);
}

}  // namespace
