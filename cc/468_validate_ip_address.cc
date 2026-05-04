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

#include "gtest/gtest.h"

namespace {
class Solution {
   private:
    std::string m_ipv4 = "IPv4";
    std::string m_ipv6 = "IPv6";
    std::string m_neither = "Neither";
    static constexpr int k_ipv4_max_val = 255;
    static constexpr int k_base = 10;

    bool ParseIpv4(std::string& s) {
        int const c = static_cast<int>(std::count(s.begin(), s.end(), '.'));
        if (c != 3) {
            return false;
        }

        auto parsedigit = [](const std::string& str) -> int {
            int sum = 0;
            for (int i = 0; i < static_cast<int>(str.size()); i++) {
                if (i == 0 && str.at(i) == '0') {
                    if (str.size() == 1) {
                        return 0;
                    }
                    return -1;
                }
                if (sum > k_ipv4_max_val) {
                    return -1;
                }

                if ('0' <= str.at(i) && str.at(i) <= '9') {
                    sum = sum * k_base + str.at(i) - '0';
                } else {
                    return -1;
                }
            }
            return sum;
        };

        std::replace(s.begin(), s.end(), '.', ' ');

        std::stringstream ss;
        ss << s;
        int i = 0;
        while (i < 4) {
            std::string tmp;
            ss >> tmp;
            if (tmp.size() == 0) {
                return false;
            }
            int const ret = parsedigit(tmp);
            if (!(0 <= ret && ret <= k_ipv4_max_val)) {
                return false;
            }
            i++;
        }
        return true;
    }

    bool ParseIpv6(std::string& s) {
        constexpr int k_colon_count = 7;
        int const sum = static_cast<int>(std::count(s.begin(), s.end(), ':'));
        if (sum != k_colon_count) {
            return false;
        }

        auto parsehex = [](const std::string& str) -> bool {
            if (str.size() <= 0 || str.size() > 4) {
                return false;
            }

            for (auto& ptr : str) {
                if ('0' <= ptr && ptr <= '9') {
                    continue;
                }
                if ('a' <= ptr && ptr <= 'f') {
                    continue;
                }
                if ('A' <= ptr && ptr <= 'F') {
                    continue;
                }

                return false;
            }
            return true;
        };

        std::replace(s.begin(), s.end(), ':', ' ');
        std::stringstream ss;
        ss << s;

        std::string tmp;
        int i = 0;
        while (ss >> tmp) {
            if (!parsehex(tmp)) {
                return false;
            }
            i++;
        }

        return i == 8;
    }

   public:
    std::string ValidIpAddress(std::string query_ip) {
        auto it1 = std::find_if(query_ip.begin(), query_ip.end(),
                           [](const char& c) { return c == '.'; });
        if (it1 != query_ip.end() && ParseIpv4(query_ip)) {
            return m_ipv4;
        }

        auto it = std::find_if(query_ip.begin(), query_ip.end(),
                          [](const char& c) { return c == ':'; });
        if (it != query_ip.end() && ParseIpv6(query_ip)) {
            return m_ipv6;
        }

        return m_neither;
    }
};

TEST(ValidateIpAddress, t0) {
    std::string const query_ip = "192.0.0.1";
    std::string const output = "IPv4";
    // Explanation: This is a valid IPv4 address, return "IPv4".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}
TEST(ValidateIpAddress, t1) {
    std::string const query_ip = "172.16.254.1";
    std::string const output = "IPv4";
    // Explanation: This is a valid IPv4 address, return "IPv4".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t2) {
    std::string const query_ip = "2001:0db8:85a3:0:0:8A2E:0370:7334";
    std::string const output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t3) {
    std::string const query_ip = "2001:0db8:85a3::8A2E:037j:7334";
    std::string const output = "Neither";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t4) {
    std::string const query_ip = "02001:0db8:85a3:0000:0000:8a2e:0370:7334";
    std::string const output = "Neither";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t5) {
    std::string const query_ip = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    std::string const output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t6) {
    std::string const query_ip = "2001:db8:85a3:0:0:8A2E:0370:7334";
    std::string const output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t7) {
    std::string const query_ip = "2001:db8:85a3:0:0:8A2E:0370:7334";
    std::string const output = "IPv6";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddress, t8) {
    std::string const query_ip = "2001:db8:85a3:0::8a2E:0370:7334";
    std::string const output = "Neither";
    // Explanation: This is a valid IPv6 address, return "IPv6".
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

TEST(ValidateIpAddressV2, t3) {
    std::string const query_ip = "256.256.256.256";
    std::string const output = "Neither";
    // Explanation: This is neither a IPv4 address nor a IPv6 address.
    Solution sl;
    auto ret = sl.ValidIpAddress(query_ip);
    EXPECT_EQ(ret, output);
}

}  // namespace
