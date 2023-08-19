// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A valid IP address consists of exactly four integers separated by single dots.
Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but
"0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses
that can be formed by inserting dots into s. You are not allowed to reorder or
remove any digits in s. You may return the valid IP addresses in any order.

*/

#include <set>
#include <string>
#include <vector>

using namespace std;
namespace { 
class Solution {
   public:
    vector<string> RestoreIpAddressesV1(string s) {
        vector<string> ret;
        return ret;
    }
    vector<std::string> v;
    void Check(string s, string ans, int len, int index) {
        if ((int)s.length() == index && len == 0) {
            ans.pop_back();
            v.push_back(ans);
            return;
        }

        if (len == 0 || ((int)s.length() - index) > len * 3) {
            return;
        }

        if (s[index] == '0') {
            Check(s, ans + s[index] + ".", len - 1, index + 1);
            return;
        }

        int c = index + 2;
        if (c > (int)s.length() - 1) {
            c = s.length() - 1;
        }

        string x = "";
        for (int i = index; i <= c; i++) {
            x += s[i];
            if (x.length() == 3 && x > "255") {
                break;
            }

            Check(s, ans + x + ".", len - 1, i + 1);
        }
    }

    vector<string> RestoreIpAddresses(string s) {
        if (s.length() > 12) {
            return v;
        }

        Check(s, "", 4, 0);
        return v;
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    string s = "25525511135";
    std::vector<string> output{"255.255.11.135", "255.255.111.35"};
    Solution sl;
    auto ret = sl.RestoreIpAddresses(s);
    set<std::string> ret_set(ret.begin(), ret.end());
    set<std::string> out_set(output.begin(), output.end());
    EXPECT_EQ(out_set, ret_set);
}

TEST(t0, t2) {
    string s = "0000";
    std::vector<string> output{"0.0.0.0"};
    Solution sl;
    auto ret = sl.RestoreIpAddresses(s);
    set<std::string> ret_set(ret.begin(), ret.end());
    set<std::string> out_set(output.begin(), output.end());
    EXPECT_EQ(out_set, ret_set);
}

TEST(t0, t3) {
    string s = "101023";
    std::vector<string> output{"1.0.10.23", "1.0.102.3", "10.1.0.23",
                               "10.10.2.3", "101.0.2.3"};
    Solution sl;
    auto ret = sl.RestoreIpAddresses(s);
    set<std::string> ret_set(ret.begin(), ret.end());
    set<std::string> out_set(output.begin(), output.end());
    EXPECT_EQ(out_set, ret_set);
}

}
