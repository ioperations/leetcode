// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if
IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.

A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and
xi cannot contain leading zeros. For example, "192.168.1.1" and "192.168.1.0"
are valid IPv4 addresses while "192.168.01.1", "192.168.1.00", and "192.168@1.1"
are invalid IPv4 addresses.

A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:

1 <= xi.length <= 4
xi is a hexadecimal string which may contain digits, lowercase English letter
('a' to 'f') and upper-case English letters ('A' to 'F'). Leading zeros are
allowed in xi. For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and
"2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while
"2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334"
are invalid IPv6 addresses.


*/

#include <algorithm>
#include <sstream>
#include <string>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   private:
    std::string ipv4 = "IPv4";
    std::string ipv6 = "IPv6";
    std::string neither = "Neither";

    bool ParseIpv4(std::string &s) {
        // pass
        int c = count(s.begin(), s.end(), '.');
        if (c != 3) return false;

        auto parsedigit = [](const std::string &s) -> int {
            int sum = 0;
            for (int i = 0; i < (int)s.size(); i++) {
                if (i == 0 && s[i] == '0') {
                    if (s.size() == 1) return 0;
                    return -1;
                }
                if (sum > 255) return -1;  // 避免某个数字造成溢出

                if ('0' <= s[i] && s[i] <= '9') {
                    sum = sum * 10 + s[i] - '0';
                } else {
                    return -1;
                }
            }
            return sum;
        };

        replace(s.begin(), s.end(), '.', ' ');

        stringstream ss;
        ss << s;
        int i = 0;
        while (i < 4) {
            string tmp;
            ss >> tmp;
            if (tmp.size() == 0) {
                return false;
            }
            int ret = parsedigit(tmp);
            if (!(0 <= ret && ret <= 255)) {
                return false;
            }
            i++;
        }
        return true;
    }

    bool ParseIpv6(std::string &s) {
        // pass
        int sum = count(s.begin(), s.end(), ':');
        if (sum != 7) return false;

        auto parsehex = [](const std::string &s) -> int {
            if (s.size() <= 0 || s.size() > 4) return false;

            for (auto &ptr : s) {
                if ('0' <= ptr && ptr <= '9') continue;
                if ('a' <= ptr && ptr <= 'f') continue;
                if ('A' <= ptr && ptr <= 'F') continue;

                return false;
            }
            return true;
        };

        replace(s.begin(), s.end(), ':', ' ');
        stringstream ss;
        ss << s;

        std::string tmp;
        int i = 0;
        while (ss >> tmp) {
            if (!parsehex(tmp)) return false;
            i++;
        }

        return i == 8;
    }

   public:
    string ValidIpAddress(string query_ip) {
        // maybe ipv4
        auto it1 = find_if(query_ip.begin(), query_ip.end(),
                           [](const char &c) { return c == '.'; });
        if (it1 != query_ip.end() && ParseIpv4(query_ip)) return ipv4;

        // maybe ipv6
        auto it = find_if(query_ip.begin(), query_ip.end(),
                          [](const char &c) { return c == ':'; });
        if (it != query_ip.end() && ParseIpv6(query_ip)) return ipv6;

        return neither;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t0) {
    string query_ip = "192.0.0.1";
    string output = "IPv4";
    // Explanation: This is a valid IPv4 address, return "IPv4".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}
TEST(t0, t1) {
    string query_ip = "172.16.254.1";
    string output = "IPv4";
    // Explanation: This is a valid IPv4 address, return "IPv4".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string query_ip = "2001:0db8:85a3:0:0:8A2E:0370:7334";
    string output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string query_ip = "2001:0db8:85a3::8A2E:037j:7334";
    string output = "Neither";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t4) {
    string query_ip = "02001:0db8:85a3:0000:0000:8a2e:0370:7334";
    string output = "Neither";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t5) {
    string query_ip = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    string output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t6) {
    string query_ip = "2001:db8:85a3:0:0:8A2E:0370:7334";
    string output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t7) {
    string query_ip = "2001:db8:85a3:0:0:8A2E:0370:7334";
    string output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t0, t8) {
    string query_ip = "2001:db8:85a3:0::8a2E:0370:7334";
    string output = "Neither";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(t1, t3) {
    string query_ip = "256.256.256.256";
    string output = "Neither";
    // Explanation: This is neither a IPv4 address nor a IPv6 address.
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

}
