///
/*

    问题描述
        有N若干层楼[1-N]，若K干个鸡蛋(K至少为1) 现在确定这栋楼存在楼层0<= F <= N
，( (
    在这层楼将鸡蛋扔下去，鸡蛋恰好没摔碎，(高于F的楼层都会碎。低于F的楼层都不会碎)，
    现在问你 ，最坏的情况下，你至少要仍几次鸡蛋，才能确定这个楼层F呢?

    分析
        有七个楼层 1 个鸡蛋
            最坏情况肯定是把这7个楼层穷举完，最坏就是7

        有7个楼层 两个鸡蛋
            最坏情况就是
                      /  第一次 在 1 楼仍 没碎 => 在 2-7 层用 2个鸡蛋仍 \
                      |                                                   最大值
                      |                   碎了 => 在 0-0 层用 1个鸡蛋仍 /
                      |  第一次 在 2 楼仍 没碎 => 在 3-7 层用 2个鸡蛋仍
                      |                   碎了 => 在 0-1 层用 1个鸡蛋仍
                      |  第一次 在 3 楼仍 ...
                      |
这些情况的最小值     <
                      |
                      |
                      |
                      |
                      \
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>

/// N 表示 楼层 一共高度
/// K 表示 鸡蛋一共有多少个
int ReturnMinDropTime(int n, int k) {
    std::function<int(int, int)> dp_fun = [&dp_fun](int n, int k) -> int {
        if (n == 0) {
            return 0;
        }
        if (k == 1) {
            return n;
        }
        int res = std::numeric_limits<int>::max();

        for (int i = 1; i <= n; ++i) {
            res = std::min(res, std::max({
                                    dp_fun(n - i, k - 1)  // 碎了
                                    ,
                                    dp_fun(n, k - 1)  // 没碎
                                }) + 1);
        }
        return res;
    };

    return dp_fun(n, k);
}

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    EXPECT_EQ(ReturnMinDropTime(7, 1), 7);
    EXPECT_EQ(ReturnMinDropTime(14, 1), 14);
    EXPECT_GE(ReturnMinDropTime(14, 2), 15);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
