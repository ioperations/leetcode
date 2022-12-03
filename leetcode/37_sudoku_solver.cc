/// leetcode 数独游戏
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace std;
class Solution {
   public:
    void solveSudoku(vector<vector<char>>& board);

   private:
    bool valid(vector<vector<char>>& board);
    /// **get candidate using the position**
    /// * NOTE: this function do have sequence dependency cause it use global
    /// state
    /// * to determine thoes candiadate's size is 0 indicating the previous
    /// * arrangement is wrong
    vector<char> getpositioncandidate(int i, int j);
};

/// 横着没有重复 竖着没有重复 九宫格内没有重复
bool Solution::valid(vector<vector<char>>& board) { return false; }

/// 将数独棋盘填充完整
/// 暴力破解
void Solution::solveSudoku(vector<vector<char>>& board) {
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

int main(int argc, char* argv[]) {
    Solution p;
    vector<char> v_1({'5', '3', '.', '.', '7', '.', '.', '.', '.'});
    vector<char> v_2({'6', '.', '.', '1', '9', '5', '.', '.', '.'});
    vector<char> v_3({'.', '9', '8', '.', '.', '.', '.', '6', '.'});
    vector<char> v_4({'8', '.', '.', '.', '6', '.', '.', '.', '3'});
    vector<char> v_5({'4', '.', '.', '8', '.', '3', '.', '.', '1'});
    vector<char> v_6({'7', '.', '.', '.', '2', '.', '.', '.', '6'});
    vector<char> v_7({'.', '6', '.', '.', '.', '.', '2', '8', '.'});
    vector<char> v_8({'.', '.', '.', '4', '1', '9', '.', '.', '5'});
    vector<char> v_9({'.', '.', '.', '.', '8', '.', '.', '7', '9'});

    vector<vector<char>> v({v_1, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9});

    p.solveSudoku(v);

    for (auto& p : v) {
        for (auto& z : p) {
            std::cout << z << " ";
        }
        std::cout << std::endl;
    }

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
