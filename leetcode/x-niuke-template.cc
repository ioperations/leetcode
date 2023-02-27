#include <iostream>

std::string Func(const char *s, int len) {
    if (len == 0) {
        return "";
    }

    return Func(s + 1, len - 1) + *s;
}

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    std::string str{};
    std::cin >> str;
    std::string t = func(str.c_str(), str.size());

    std::cout << t << std::endl;
    return 0;
}

#endif
