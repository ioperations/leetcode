/*.
 * You are given two integers num1 and num2 representing an inclusive range
 *  [num1, num2].
 *
 *  The waviness of a number is defined as the total count of its peaks and
 * valleys:
 *
 *  A digit is a peak if it is strictly greater than both of its immediate
 *  neighbors. A digit is a valley if it is strictly less than both of its
 * immediate neighbors. The first and last digits of a number cannot be peaks or
 * valleys. Any number with fewer than 3 digits has a waviness of 0. Return the
 * total sum of waviness for all numbers in the range [num1, num2].
 *
 * 1 <= num1 <= num2 <= 10**15
 */
#include <cstring>
#include <string>
using namespace std;

namespace {
class Solution {
   public:
    Solution() {
        memset(m_memo_cnt, -1, sizeof(m_memo_cnt));
        memset(m_memo_sum, -1, sizeof(m_memo_sum));
    }
    long long TotalWaviness(long long num1, long long num2) {
        // calculate the sum of the volatility values of all numbers in [0, num]

        return Solve(num2) - Solve(num1 - 1);
    }

   private:
    using ll = long long;
    auto Solve(ll num) -> ll {
        // if the fluctuation value of numbers less than 3 is 0
        if (num < 100) {
            return 0;
        }
        m_s = to_string(num);
        m_n = m_s.length();
        // memoized search uses two independent arrays
        // memo_cnt[pos][x][y]: the number of valid filling schemes where
        // the current digit is at position pos, and the previous two digits
        // are x and y

        // pass dfs as the first parameter
        auto [_, totalSum] = Dfs(0, -1, -1, true, true);
        return totalSum;
    };
    string m_s;
    ll m_memo_cnt[16][10][10]{};
    // memo_sum[pos][x][y]: the fluctuation value when the current
    // position is pos, and the two left digits are x and y
    ll m_memo_sum[16][10][10]{};

    std::size_t m_n{0};

    auto Dfs(int pos, int prev, int curr, bool is_limit, bool is_leading)
        -> pair<ll, ll> {
        // end position
        if (pos == m_n) {
            return {1, 0};
        }
        // use memoization only when not bounded by an upper limit and
        // without leading zeros
        if (!is_limit && !is_leading && prev >= 0 && curr >= 0) {
            if (m_memo_cnt[pos][prev][curr] != -1) {
                return {m_memo_cnt[pos][prev][curr],
                        m_memo_sum[pos][prev][curr]};
            }
        }

        // calculate the number of schemes and fluctuation value under
        // the current conditions
        ll cnt = 0, sum = 0;
        int up = is_limit ? m_s[pos] - '0' : 9;
        for (int digit = 0; digit <= up; ++digit) {
            bool new_leading = is_leading && (digit == 0);
            // the previous number is updated to curr
            int new_prev = curr;
            // the current number is updated to digit
            int new_curr = new_leading ? -1 : digit;
            auto [subCnt, subSum] = Dfs(pos + 1, new_prev, new_curr,
                                        is_limit && (digit == up), new_leading);
            // only calculate the fluctuation value when there are no
            // leading zeros
            if (!new_leading && prev >= 0 && curr >= 0) {
                // when the digit is a peak or a valley, update the
                // current fluctuation value
                if ((prev < curr && curr > digit) ||
                    (prev > curr && curr < digit)) {
                    sum += subCnt;
                }
            }

            cnt += subCnt;
            sum += subSum;
        }

        if (!is_limit && !is_leading && prev >= 0 && curr >= 0) {
            // update the memoization array
            m_memo_cnt[pos][prev][curr] = cnt;
            m_memo_sum[pos][prev][curr] = sum;
        }

        return {cnt, sum};
    };
};
}  // namespace

#include <gtest/gtest.h>

TEST(t0, t1) {
    long long num1 = 120, num2 = 130;

    long long output = 3;
    /*
     * Explanation:
     * In the range [120, 130]:
     * 120: middle digit 2 is a peak, waviness = 1.
     * 121: middle digit 2 is a peak, waviness = 1.
     * 130: middle digit 3 is a peak, waviness = 1.
     * All other numbers in the range have a waviness of 0.
     * Thus, total waviness is 1 + 1 + 1 = 3.
     */
    Solution sl;
    long long ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

TEST(t0, t2) {
    long long num1 = 198, num2 = 202;
    long long output = 3;
    /*
     * Explanation:
     * In the range [198, 202]:
     * 198: middle digit 9 is a peak, waviness = 1.
     * 201: middle digit 0 is a valley, waviness = 1.
     * 202: middle digit 0 is a valley, waviness = 1.
     * All other numbers in the range have a waviness of 0.
     * Thus, total waviness is 1 + 1 + 1 = 3.
     **/

    Solution sl;
    long long ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

TEST(t0, t3) {
    long long num1 = 4848, num2 = 4848;

    long long output = 2;
    /*
     * Explanation:
     * Number 4848: the second digit 8 is a peak, and the third digit 4 is a
     * valley, giving a waviness of 2.
     **/

    Solution sl;
    long long ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
