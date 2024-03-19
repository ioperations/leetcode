// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <cstdlib>
#include <limits>
#include <string>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    Solution(){};
    virtual ~Solution(){};
    /**
     * @brief 反转数字
     * @param @x 数字
     * @return  返回后的数字
     */
    int ReverseV1(int x) {
        if (x == -2147483648) {
            return 0;
        }
        if (x < 0) {
            return -ReverseV1(-x);
        }
        int ret = 0;
        while (x) {
            if ((double)(std::numeric_limits<int>::max() - (x % 10)) / 10 >=
                ret) {
                ret = ret * 10 + (x % 10);
                x /= 10;
            } else {
                return 0;
            }
        }

        return ret;
    }

    int Reverse(int x) {
        if (x < 0) {
            auto ret = Reverse(std::to_string(std::abs(x)));
            if (OutOfRange(ret)) {
                return 0;
            }
            return -atol(ret.c_str());
        }

        auto str = std::to_string(std::abs(x));
        auto ret = Reverse(str);

        if (OutOfRange(ret)) {
            return 0;
        }

        return atol(ret.c_str());
    }

   private:
    /**
     * @brief 反转字符串
     * @param @s 输入字符串
     * @return
     */
    static std::string Reverse(std::string s) {
        if (s.size() <= 1) {
            return s;
        }

        return Reverse(s.substr(1)) + s[0];
    }

    /**
     * @brief 确定字符串是不是会越界
     */
    static bool OutOfRange(const std::string &s) {
        const int32_t max = std::numeric_limits<int32_t>::max();
        int32_t sum = 0;
        for (const auto &ptr : s) {
            if ('0' <= ptr && ptr <= '9') {
                if (((double)(max - (ptr - '0')) / 10) >= sum) {
                    // 怎么老是报错 说是越界
                    sum = sum * 10 + ptr - '0';
                } else {
                    return true;
                }
            } else {
                return true;
            }
        }
        return false;
    }
};

TEST(reverse_integer, t1) {
    Solution s;
    auto ret = s.Reverse(100);

    EXPECT_EQ(ret, 1);
}

TEST(reverse_integer_v2, t1) {
    Solution s;
    auto ret = s.ReverseV1(100);

    EXPECT_EQ(ret, 1);
}

TEST(reverse_integer, t2) {
    Solution s;
    auto ret = s.Reverse(-101);

    EXPECT_EQ(ret, -101);
}

TEST(reverse_integer_v2, t2) {
    Solution s;
    auto ret = s.ReverseV1(-101);

    EXPECT_EQ(ret, -101);
}

TEST(reverse_integer, t3) {
    Solution s;
    auto ret = s.Reverse(1534236469);

    EXPECT_EQ(ret, 0);
}

TEST(reverse_integer_v2, t3) {
    Solution s;
    auto ret = s.ReverseV1(1534236469);

    EXPECT_EQ(ret, 0);
}

TEST(reverse_integer, t4) {
    Solution s;
    auto ret = s.Reverse(-2147483412);

    EXPECT_EQ(ret, -2143847412);
}

TEST(reverse_integer, t5) {
    Solution s;
    auto ret = s.Reverse(-2147483648);

    EXPECT_EQ(ret, 0);
}

TEST(reverse_integer_v2, t4) {
    Solution s;
    auto ret = s.ReverseV1(-2147483412);

    EXPECT_EQ(ret, -2143847412);
}

TEST(reverse_integer_v2, t5) {
    Solution s;
    auto ret = s.ReverseV1(-2147483648);

    EXPECT_EQ(ret, 0);
}

}  // namespace
