// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <cstdlib>
#include <iostream>

enum type {
    ENGLISH_CHAR = 0,
    SPACE,
    NUMBER,
    OTHERS,
    LENGTH,
};

void Func(const char *s, int len) {
    int classfy[type::LENGTH] = {0};

    for (int i = 0; i < len; ++i) {
        if (('a' <= *(s + i) && *(s + i) <= 'z') ||
            ('A' <= *(s + i) && *(s + i) <= 'Z')) {
            classfy[type::ENGLISH_CHAR]++;
        } else if ('0' <= *(s + i) && *(s + i) <= '9') {
            classfy[type::NUMBER]++;
        } else if (' ' == *(s + i)) {
            classfy[type::SPACE]++;
        } else {
            classfy[type::OTHERS]++;
        }
    }

    for (int i = 0; i < type::LENGTH; ++i) {
        std::cout << classfy[i] << std::endl;
    }
}

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    std::string s = "1qazxsw23 edcvfr45tgbn hy67uj m,ki89ol.\\\\/;p0-=\\\\][";
    testing::internal::CaptureStdout();
    Func(s.c_str(), s.size());
    std::string result = testing::internal::GetCapturedStdout();
    std::string expected("26\n3\n10\n12\n");
    EXPECT_EQ(result, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    std::string str{};
    while (std::getline(std::cin, str)) {
        func(str.c_str(), str.size());
    }

    return 0;
}

#endif
