/// 找两个数的最小公倍数

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

std::int64_t ReturnMinmiumOfTwoInteger(int64_t num1, int64_t num2) {
    /// if num1 and num2 if 素数
    /// return num1 * num2

    /// 找到 自己公约数
    /// 24 = 4*6 = 3*8 = 2*2*2*3

    std::int64_t bigger = num1 > num2 ? num1 : num2;
    std::int64_t* dp = new std::int64_t[bigger + 1];

    for (std::int64_t i = 0; i <= bigger; ++i) {
        *(dp + i) = -1;
    }

    /// dp[i] 表示 这个数字 i 除了自己和 1 以外的最大公约数
    for (std::int64_t i = 3; i <= bigger; ++i) {
        for (std::int64_t j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                *(dp + i) = j;
            }
        }
    }

    /// 公约数 -> 多少个

    /// num2 is a array
    /// for all 公约数  i in num2
    ///     if i in num1
    ///         num1[i]--
    ///     else
    ///        continue

    /// result = 1;
    /// for i in num2
    ///     for j in num1
    ///         result = i*j*result;

    std::vector<std::int64_t> num1_arr{};
    std::int64_t i = num1;
    for (; dp[i] != -1;) {
        num1_arr.push_back(i / dp[i]);
        i = dp[i];
    }
    num1_arr.push_back(i);

    /*
    for (std::int64_t i = 0; i < num1_arr.size(); ++i) {
        std::cout << num1_arr[i] << " ";
    }
    std::cout << std::endl;
    */

    std::vector<std::int64_t> num2_arr{};
    i = num2;
    for (; dp[i] != -1;) {
        num2_arr.push_back(i / dp[i]);
        i = dp[i];
    }
    num2_arr.push_back(i);

    /*
    for (std::int64_t i = 0; i < num2_arr.size(); ++i) {
        std::cout << num2_arr[i] << " ";
    }
    std::cout << std::endl;
    */

    std::vector<std::int64_t> v(bigger);

    std::set_intersection(num2_arr.begin(), num2_arr.end(), num1_arr.begin(),
                          num1_arr.end(), v.begin());

    std::int64_t divide = 1;

    auto pend = std::remove_if(v.begin(), v.end(),
                               [](const std::int64_t& s) { return s == 0; });

    v.resize(pend - v.begin());
    auto it2 = std::max_element(v.begin(), v.end());
    if (it2 != std::end(v)) {
        divide = *it2;
        /* std::cout << "divide is " << divide << std::endl; */
    }
    /*
    for (std::int64_t i = 0; i < v.size(); ++i) {
        std::cout << "v[" << i << "] is " << v[i] << " ";
    }
    std::cout << " --- " << std::endl;
    */

    delete[] dp;

    return (num1 / divide) * num2;
}

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

TEST(t1, t2) {
    std::int64_t ret = ReturnMinmiumOfTwoInteger(5, 7);
    EXPECT_EQ(ret, 35);
}

TEST(t1, t3) {
    std::int64_t ret = ReturnMinmiumOfTwoInteger(2, 4);
    EXPECT_EQ(ret, 4);
}

TEST(t2, t3) {
    std::int64_t ret = ReturnMinmiumOfTwoInteger(1, 2);
    EXPECT_EQ(ret, 2);
}

TEST(t3, t3) {
    std::int64_t ret = ReturnMinmiumOfTwoInteger(502, 94278);
    EXPECT_EQ(ret, 23663778);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    int64 num1, num2;
    std::cin >> num1;
    std::cin >> num2;
    std::cout << returnMinmiumOfTwoInteger(num1, num2) << std::endl;
    return 0;
}
#endif
