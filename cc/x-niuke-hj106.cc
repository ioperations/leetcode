// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <gtest/gtest.h>

#include <iostream>

namespace {
std::string ReturnS(const char *s, int len) {
    if (len == 0) {
        return "";
    }

    return ReturnS(s + 1, len - 1) + *s;
}

TEST(t1, t2) {
    std::string s = "1516000";
    std::string rets = ReturnS(s.c_str(), s.size());
    EXPECT_EQ(rets, std::string("0006151"));
}
}  // namespace
