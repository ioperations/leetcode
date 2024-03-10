// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string AddBinary(const string &a, const string &b) {
        const char map[] = {'0', '1', '0', '1'};
        for (auto a_it = a.rbegin(), b_it = b.rbegin();

             a_it != a.rend() || b_it != b.rend() || carrier;) {
            int this_bit = 0;

            if (a_it == a.rend() && b_it != b.rend()) {
                this_bit = (*b_it - '0') + carrier;
                b_it++;
            } else if (b_it == b.rend() && a_it != a.rend()) {
                this_bit = (*a_it - '0') + carrier;
                a_it++;
            } else if (b_it != b.rend() && a_it != a.rend()) {
                this_bit = (*a_it - '0') + (*b_it - '0') + carrier;
                a_it++;
                b_it++;
            } else if (carrier) {
                this_bit = carrier;
            }
            carrier = this_bit >= 2 ? 1 : 0;
            ret = map[this_bit] + ret;
        }
        return ret;
    }

   private:
    int __attribute__((unused)) carrier = 0;
    string ret = "";
};

TEST(_add_binaryv2, t0) {
    string s = "1111";
    string b = "10101";

    Solution sl;
    auto ret = sl.AddBinary(s, b);

    EXPECT_EQ(ret, "100100");
}

TEST(_add_binaryv2, t1) {
    string s = "11";
    string b = "1";

    Solution sl;
    auto ret = sl.AddBinary(s, b);

    EXPECT_EQ(ret, "100");
}

}  // namespace
