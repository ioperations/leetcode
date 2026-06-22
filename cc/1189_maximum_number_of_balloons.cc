/*Given a string text, you want to use the characters of text to form as many
 * instances of the word "balloon" as possible.
 *
 * You can use each character in text at most once. Return the maximum number of
 * instances that can be formed.
 *
 *
 * // 1 <= text.length <= 104
 * // text consists of lower case English letters only.
 */

#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;
namespace {

class Solution {
   private:
    int Min(int m, int n) { return std::min(m, n); }

    template <typename N, typename... T>
    int Min(N m, N n, T... q) {
        return Min(m, Min(n, q...));
    }

   public:
    int MaxNumberOfBalloons(const string& text) {
        unordered_map<char, int> hm;
        for (auto& p : text) {
            if (p == 'b' || p == 'a' || p == 'l' || p == 'o' || p == 'n') {
                hm[p]++;
            }
        }

        return Min<int>(hm['b'], hm['a'], hm['l'] / 2, hm['o'] / 2, hm['n']);
    }
};

class SolutionV2 {
   private:
    int Min(std::initializer_list<int> list) {
        return *std::min_element(list.begin(), list.end());
    }

   public:
    int MaxNumberOfBalloons(const string& text) {
        unordered_map<char, int> hm;
        for (auto& p : text) {
            if (p == 'b' || p == 'a' || p == 'l' || p == 'o' || p == 'n') {
                hm[p]++;
            }
        }

        return Min({hm['b'], hm['a'], hm['l'] / 2, hm['o'] / 2, hm['n']});
    }
};

}  // namespace

#include <gtest/gtest.h>

TEST(maxNumberOfBalloons, t1) {
    string text = "nlaebolko";
    int output = 1;
    Solution sl;
    auto ret = sl.MaxNumberOfBalloons(text);
    EXPECT_EQ(output, ret);
}
TEST(maxNumberOfBalloons, t2) {
    string text = "loonbalxballpoon";
    int output = 2;
    Solution sl;
    auto ret = sl.MaxNumberOfBalloons(text);
    EXPECT_EQ(output, ret);
}

TEST(maxNumberOfBalloons, t3) {
    string text = "leetcode";
    int output = 0;
    Solution sl;
    auto ret = sl.MaxNumberOfBalloons(text);
    EXPECT_EQ(output, ret);
}

TEST(maxNumberOfBalloonsV2, t1) {
    string text = "nlaebolko";
    int output = 1;
    SolutionV2 sl;
    auto ret = sl.MaxNumberOfBalloons(text);
    EXPECT_EQ(output, ret);
}
TEST(maxNumberOfBalloonsV2, t2) {
    string text = "loonbalxballpoon";
    int output = 2;
    SolutionV2 sl;
    auto ret = sl.MaxNumberOfBalloons(text);
    EXPECT_EQ(output, ret);
}

TEST(maxNumberOfBalloonsV2, t3) {
    string text = "leetcode";
    int output = 0;
    SolutionV2 sl;
    auto ret = sl.MaxNumberOfBalloons(text);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
