#include <iostream>

int Func(std::string& s1, std::string& s2) {
    if (s2.size() > s1.size()) {
        return Func(s2, s1);
    }

    // s1 的 值是相对较少的

    return 0;
}

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    std::string s1 = "asdfas";
    std::string s2 = "werasdfaswer";
    EXPECT_EQ(Func(s1, s2), 6);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    std::string str{};
    std::cin >> str;
    std::string str2{};
    std::cin >> str2;
    int t = func(str, str2);

    std::cout << t << std::endl;
    return 0;
}

#endif
