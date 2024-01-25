// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// 这个题目考验的是对 编译器 的 表达式 执行的过程
/// 中缀表达式 转为 后缀表达式
#include <iostream>
#include <stack>
using namespace std;
int pos;

int Result(const string &data) {
    int num = 0;
    char flag = '+';
    stack<int> stk;
    int len = data.length();
    while (pos < len) {
        if (data[pos] == '(') {
            pos++;
            num = Result(data);
        }
        while (pos < len && isdigit(data[pos])) {
            num = num * 10 + data[pos] - '0';
            pos++;
        }
        switch (flag) {
            case '+': {
                stk.push(num);
                break;
            }
            case '-': {
                stk.push(-num);
                break;
            }
            case '*': {
                stk.top() *= num;
                break;
            }
            case '/': {
                stk.top() /= num;
                break;
            }
        }
        num = 0;
        flag = data[pos];
        if (data[pos] == ')') {
            ++pos;
            break;
        }
        ++pos;
    }
    int sum = 0;
    while (!stk.empty()) {
        sum += stk.top();
        stk.pop();
    }
    return sum;
}
#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    pos = 0;
    const char *s = "400+5";
    int ret = Result(s);
    EXPECT_EQ(ret, 405);
}

TEST(t1, t3) {
    pos = 0;
    const char *s = "4*(2+5)";
    int ret = Result(s);
    EXPECT_EQ(ret, 28);
}

TEST(t1, t4) {
    pos = 0;
    const char *s = "4*(2+(5-7))";
    int ret = Result(s);
    EXPECT_EQ(ret, 0);
}

TEST(t1, t5) {
    pos = 0;
    const char *s = "(2+(5-7))*(-4)";
    int ret = Result(s);
    EXPECT_EQ(ret, 0);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    const char *str = "400*(4+4)";
    pos = 0;
    cout << result(str) << endl;
    return 0;
}
#endif