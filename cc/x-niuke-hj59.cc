// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <gtest/gtest.h>

#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace {
/// output the first char existing only once
void Process(std::string str) {
    for (int i = 0; i < (int)str.size(); i++) {
        if (str.find_first_of(str[i]) == str.find_last_of(str[i])) {
            cout << str[i] << endl;
            break;
        }
        if (i == (int)str.size() - 1) cout << -1 << endl;
    }
}

TEST(ta, t2) {
    std::string ss("aabb");
    testing::internal::CaptureStdout();
    Process(ss);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, std::string("-1\n"));
}
TEST(t1, t2) {
    std::string ss("asdfasdfo");
    testing::internal::CaptureStdout();
    Process(ss);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, std::string("o\n"));
}
}  // namespace
