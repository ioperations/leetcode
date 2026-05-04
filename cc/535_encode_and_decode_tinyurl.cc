// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**
inyURL is a URL shortening service where you enter a URL such as
https://leetcode.com/problems/design-tinyurl and it returns a short URL such as
namespace {
http://tinyurl.com/4e9iAk. Design a class to encode a URL and decode a tiny URL.

There is no restriction on how your encode/decode algorithm should work. You
just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can
be decoded to the original URL.

Implement the Solution class:

Solution() Initializes the object of the system.
String encode(String longUrl) Returns a tiny URL for the given longUrl.
String decode(String shortUrl) Returns the original long URL for the given
shortUrl. It is guaranteed that the given shortUrl was encoded by the same
object.
*/

#include <cstdlib>
#include <random>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    unordered_map<string, string> m_um;
    int m_len = 6;

    string GenerateRandomCode(string const& long_url) {
        string code = "";

        static std::mt19937 gen{std::random_device{}()};

        for (int i = 0; i < m_len; i++) {
            std::uniform_int_distribution<> dis(0, 2);
            int const type = dis(gen);

            if (type == 0) {  // number
                std::uniform_int_distribution<> num_dis(0, 9);
                code += static_cast<char>(num_dis(gen) + 48);
            } else if (type == 1) {  // lowercase char
                std::uniform_int_distribution<> low_dis(0, 25);
                code += static_cast<char>(low_dis(gen) + 97);
            } else {  // uppercase char
                std::uniform_int_distribution<> up_dis(0, 25);
                code += static_cast<char>(up_dis(gen) + 65);
            }
        }

        if (m_um.find(code) != m_um.end()) {
            return GenerateRandomCode(long_url);
        }
        m_um[code] = long_url;
        return code;
    }

    string GetCode(string const& short_url) {
        int const n = static_cast<int>(short_url.size());
        return short_url.substr(static_cast<size_t>(n) - static_cast<size_t>(m_len), static_cast<size_t>(m_len));
    }

   public:
    string Encode(string const& long_url) {
        string tiny_url = "http://tinyurl.com/";
        string const suffix = GenerateRandomCode(long_url);
        return tiny_url += suffix;
    }

    // Decodes a shortened URL to its original URL.
    string Decode(string const& short_url) {
        string const code = GetCode(short_url);
        return m_um[code];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

TEST(testName, testNum) {
    std::string const url = "https://leetcode.com/problems/design-tinyurl";

    Solution s;
    EXPECT_EQ(s.Decode(s.Encode(url)), url);
}

}  // namespace
