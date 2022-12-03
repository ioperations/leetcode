#include <iostream>

#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <stack>

int Getret(const char* s, int len) {
    std::stack<char> sta;

    for (int i = 0; i < len; ++i) {
        sta.push(*(s + i));
    }
    return 0;
}

TEST(t1, t2) {
    std::string s("400+5");
    int ret = Getret(s.c_str(), s.size());
    EXPECT_EQ(ret, 405);
}

TEST(t1, t3) {
    std::string s("4*(2+5)");
    int ret = Getret(s.c_str(), s.size());
    EXPECT_EQ(ret, 28);
}

TEST(t1, t4) {
    std::string s("4*(2+(5-7))");
    int ret = Getret(s.c_str(), s.size());
    EXPECT_EQ(ret, 0);
}

TEST(t1, t5) {
    std::string s("(2+(5-7))*(-4)");
    int ret = Getret(s.c_str(), s.size());
    EXPECT_EQ(ret, 28);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else
int main() {
    std::string s1;
    int ret = getline(std::cin, s1);
    std::cout << ret << std::endl;
    return 0;
}
#endif
