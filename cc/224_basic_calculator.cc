// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
224. Basic Calculator
Given a string s representing a valid expression, implement a basic calculator
to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings
as mathematical expressions, such as eval().
*/

#include <benchmark/benchmark.h>
#include <stddef.h>

#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int Calculate(string s) {
        // pass
        Token token(s);

        auto z = token.CurToken();

        while (z != Token::EOL) {
            if (z == Token::NUMBER) {
                //    int val = token.GetVal();
            } else {
            }
            token.next();
        }
        return 0;
    }
    int ApplyOp(int a, int b, char op) {
        int out = 0;

        switch (op) {
            case '+':
                out = a + b;
                break;
            case '-':
                out = a - b;
                break;
            case '*':
                out = a * b;
                break;
            case '/':
                out = a / b;
                break;
        }
        return out;
    }

    class Token {
       public:
        // s consists of digits, '+', '-', '(', ')', and ' '.
        enum token_type {
            PLUS,
            MINUS,
            NUMBER,
            LEFT_PARAM,
            RIGHT_PARAM,
            EOL,
        };

        Token(std::string s) : s(s) {
            index = -1;
            next();
        }
        void next() {
            index++;
            val = 0;
            bool val_set = false;
            if (index >= s.size()) {
                cur_token = EOL;
                return;
            }
            while (index < s.size()) {
                if (' ' == s[index]) {
                    index++;
                    continue;
                }
                if ('0' <= s[index] && s[index] <= '9') {
                    val_set = true;
                    cur_token = NUMBER;
                    val = val * 10 + s[index] - '0';
                }

                if (val_set) {
                    if ((index + 1) < s.size()) {
                        if ('0' <= s[index + 1] && s[index + 1] <= '9') {
                            index++;
                            continue;
                        }
                        break;
                    }
                    break;
                }
                if ('+' == s[index]) {
                    cur_token = PLUS;
                    break;
                }
                if ('-' == s[index]) {
                    cur_token = MINUS;
                    break;
                }
                if ('(' == s[index]) {
                    cur_token = LEFT_PARAM;
                    break;
                }
                if (')' == s[index]) {
                    cur_token = RIGHT_PARAM;
                    break;
                }
                cur_token = EOL;
                break;
            }
        }
        token_type CurToken() { return cur_token; }

        int GetVal() { return val; }

       private:
        std::string s;
        int val;
        size_t index;
        token_type cur_token;
    };
};

class SolutionV2 {
   public:
    int Calculate(string s) {
        int res = 0, sign = 1, n = s.size();
        stack<int> stk;
        for (int i = 0; i < n; i++) {
            const char c = s[i];
            if (c >= '0' && c <= '9') {
                int num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                res += sign * num;
                i--;
            } else if (c == '+')
                sign = 1;
            else if (c == '-')
                sign = -1;
            else if (c == '(') {
                stk.push(res);
                stk.push(sign);
                res = 0;
                sign = 1;
            } else if (c == ')') {
                res *= stk.top();
                stk.pop();
                res += stk.top();
                stk.pop();
            }
        }
        return res;
    }
};

class SolutionV3 {
   public:
    int Calculate(string s) {
        // Stack to store numbers
        stack<int> nums;

        // Stack to store operators
        stack<char> ops;

        for (int i = 0; i < (int)s.size(); ++i) {
            const char ch = s[i];

            // If current is space, skip it
            if (ch == ' ') continue;

            // If current is a number
            if (isdigit(ch)) {
                // Long type to prevent integer overflow
                long num = 0;

                while (i < (int)s.size() && isdigit(s[i])) {
                    num = num * 10 + s[i] - '0';
                    ++i;
                }
                nums.push(num);
                --i;
            }
            // If current is left bracket
            else if (ch == '(')
                ops.push(ch);

            // If current is right bracket
            // Solve entire bracket
            else if (ch == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    const int num2 = nums.top();
                    nums.pop();
                    const int num1 = nums.top();
                    nums.pop();

                    const int out = ApplyOp(num1, num2, ops.top());
                    ops.pop();
                    nums.push(out);
                }
                // Pop left bracket
                ops.pop();

            }
            // If current is an operator
            else {
                // While top of 'ops' has same or greater
                // precedence to current token, which
                // is an operator. Apply operator on top
                // of 'ops' to top two elements in nums stack.
                while (!ops.empty() &&
                       Precedence(ops.top()) >= Precedence(ch)) {
                    const int num2 = nums.top();
                    nums.pop();
                    const int num1 = nums.top();
                    nums.pop();

                    const int out = ApplyOp(num1, num2, ops.top());
                    ops.pop();
                    nums.push(out);
                }
                ops.push(ch);
            }
        }

        // Entire expression has been parsed at this
        // point, apply remaining ops to remaining
        // values.
        while (!ops.empty()) {
            const int num2 = nums.top();
            nums.pop();
            const int num1 = nums.top();
            nums.pop();

            const int out = ApplyOp(num1, num2, ops.top());
            ops.pop();

            nums.push(out);
        }

        return nums.top();
    }

    int ApplyOp(int a, int b, char op) {
        int out = 0;

        switch (op) {
            case '+':
                out = a + b;
                break;
            case '-':
                out = a - b;
                break;
            case '*':
                out = a * b;
                break;
            case '/':
                out = a / b;
                break;
        }
        return out;
    }

    int Precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
};

TEST(basic_calculator, t1) {
    const std::string s = "1+1";

    SolutionV2 sl;
    const int ret = sl.Calculate(s);

    EXPECT_EQ(ret, 2);
}

TEST(basic_calculator, t2) {
    const std::string s = "2-1+2";

    SolutionV2 sl;
    const int ret = sl.Calculate(s);

    EXPECT_EQ(ret, 3);
}

TEST(basic_calculator, t3) {
    const std::string s = "(1+(4+5+2)-3)+(6+8)";

    SolutionV2 sl;
    const int ret = sl.Calculate(s);

    EXPECT_EQ(ret, 23);
}

TEST(basic_calculator_v2, t1) {
    const std::string s = "1+1";

    SolutionV3 sl;
    const int ret = sl.Calculate(s);

    EXPECT_EQ(ret, 2);
}

TEST(basic_calculator_v2, t2) {
    const std::string s = "2-1+2";

    SolutionV3 sl;
    const int ret = sl.Calculate(s);

    EXPECT_EQ(ret, 3);
}

TEST(basic_calculator_v2, t3) {
    const std::string s = "(1+(4+5+2)-3)+(6+8)";

    SolutionV3 sl;
    const int ret = sl.Calculate(s);

    EXPECT_EQ(ret, 23);
}

void BenchV2(benchmark::State &state) {
    for (auto _ : state) {
        const std::string s = "(1+(4+5+2)-3)+(6+8)";

        SolutionV2 sl;
        const int ret = sl.Calculate(s);

        EXPECT_EQ(ret, 23);
    }
}
BENCHMARK(BenchV2);

void BenchV3(benchmark::State &state) {
    for (auto _ : state) {
        const std::string s = "(1+(4+5+2)-3)+(6+8)";

        SolutionV3 sl;
        const int ret = sl.Calculate(s);

        EXPECT_EQ(ret, 23);
    }
}
BENCHMARK(BenchV3);

}  // namespace
