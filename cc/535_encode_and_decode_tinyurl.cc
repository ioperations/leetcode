// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**
inyURL is a URL shortening service where you enter a URL such as
https://leetcode.com/problems/design-tinyurl and it returns a short URL such as
#include<gtest/gtest.h>
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

#include <string>
#include <unordered_map>

using namespace std;
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    unordered_map<string, string> um;
    int len = 6;

    string GenerateRandomCode(string long_url) {
        string code = "";

        for (int i = 0; i < len; i++) {
            int type = rand() % 3;

            if (type == 0) {  // number
                code += char(rand() % 10 + 48);
            } else if (type == 1) {  // lowercase char
                code += char(rand() % 26 + 97);
            } else {  // uppercase char
                code += char(rand() % 26 + 65);
            }
        }

        if (um.find(code) != um.end()) {
            return GenerateRandomCode(long_url);
        }
        um[code] = long_url;
        return code;
    }

    string GetCode(string short_url) {
        int n = short_url.size();
        return short_url.substr(n - len, len);
    }

   public:
    // Encodes a URL to a shortened URL.
    string Encode(string long_url) {
        string tiny_url = "http://tinyurl.com/";
        string suffix = GenerateRandomCode(long_url);
        return tiny_url += suffix;
    }

    // Decodes a shortened URL to its original URL.
    string Decode(string short_url) {
        string code = GetCode(short_url);
        return um[code];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

#include <gtest/gtest.h>

#include <iostream>

TEST(testName, testNum) {
    std::string url = "https://leetcode.com/problems/design-tinyurl";

    Solution s;
    EXPECT_EQ(s.Decode(s.Encode(url)), url);
}

}
