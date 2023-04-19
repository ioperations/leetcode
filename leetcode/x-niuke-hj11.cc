// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <iostream>

std::string ReturnS(const char *s, int len) {
    if (len == 0) {
        return "";
    }

    return ReturnS(s + 1, len - 1) + *s;
}

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    std::string s = "1516000";
    std::string rets = ReturnS(s.c_str(), s.size());
    EXPECT_EQ(rets, std::string("0006151"));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    std::string str{};
    std::cin >> str;
    std::string t = returnS(str.c_str(), str.size());

    std::cout << t << std::endl;
    return 0;
}

#endif
