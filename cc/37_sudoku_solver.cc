// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// leetcode 数独游戏
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace std;
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    void solveSudoku(vector<vector<char>> &board);

   private:
    bool valid(vector<vector<char>> &board);
    /// **get candidate using the position**
    /// * NOTE: this function do have sequence dependency cause it use global
    /// state
    /// * to determine thoes candiadate's size is 0 indicating the previous
    /// * arrangement is wrong
    vector<char> getpositioncandidate(int i, int j);
};

/// 横着没有重复 竖着没有重复 九宫格内没有重复
bool Solution::valid(vector<vector<char>> &board) { return false; }

/// 将数独棋盘填充完整
/// 暴力破解
void Solution::solveSudoku(vector<vector<char>> &board) {
    /// get candidate

    /// 一行中第一个空位 填充 在这个情况下填充第二个 空位（ 空位的选择
    /// 去除掉第一个已经选择了的）
    /*
        for i in line 1-9{
            // 第 i 行
            getline_candidate() -> ['2','3','4'] && schma have return.size()!
              try {

              }
          }
     */
}

}
