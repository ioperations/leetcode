/*Given an expression such as expression = "e + 8 - a + 5" and an evaluation map
such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return
a list of tokens representing the simplified expression, such as ["-1*a","14"]

An expression alternates chunks and symbols, with a space separating each chunk
and symbol. A chunk is either an expression in parentheses, a variable, or a
non-negative integer. A variable is a string of lowercase letters (not including
digits.) Note that variables can be multiple letters, and note that variables
never have a leading coefficient or unary operator like "2x" or "-x".
Expressions are evaluated in the usual order: brackets first, then
multiplication, then addition and subtraction.

For example, expression = "1 + 2 * 3" has an answer of ["7"].
The format of the output is as follows:

For each term of free variables with a non-zero coefficient, we write the free
variables within a term in sorted order lexicographically. For example, we would
never write a term like "b*a*c", only "a*b*c". Terms have degrees equal to the
number of free variables being multiplied, counting multiplicity. We write the
largest degree terms of our answer first, breaking ties by lexicographic order
ignoring the leading coefficient of the term. For example, "a*a*b*c" has
degree 4. The leading coefficient of the term is placed directly to the left
with an asterisk separating it from the variables (if they exist.) A leading
coefficient of 1 is still printed. An example of a well-formatted answer is
["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"]. Terms (including constant
terms) with coefficient 0 are not included. For example, an expression of "0"
has an output of []. Note: You may assume that the given expression is always
valid. All intermediate results will be in the range of [-231, 231 - 1].*/

#include <vector>
using namespace std;

#include <string>
class Solution {
   public:
    vector<string> BasicCalculatorIv(string expression,
                                     vector<string>& evalvars,
                                     vector<int>& evalints) {
        vector<string> ret;
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string const expression = "e + 8 - a + 5";
    vector<string> evalvars = {"e"};
    vector<int> evalints = {1};
    vector<string> const output = {"-1*a", "14"};
    Solution sl;
    auto ret = sl.BasicCalculatorIv(expression, evalvars, evalints);
    EXPECT_EQ(ret, output);
};

TEST(t0, t2) {
    std::string const expression = "e - 8 + temperature - pressure";
    vector<string> evalvars = {"e", "temperature"};
    vector<int> evalints = {1, 12};
    vector<string> const output = {"-1*pressure", "5"};
    Solution sl;
    auto ret = sl.BasicCalculatorIv(expression, evalvars, evalints);
    EXPECT_EQ(ret, output);
};

TEST(t0, t3) {
    std::string const expression = "(e + 8) * (e - 8)";
    vector<string> evalvars = {};
    vector<int> evalints = {};
    vector<string> const output = {"1*e*e", "-64"};
    Solution sl;
    auto ret = sl.BasicCalculatorIv(expression, evalvars, evalints);
    EXPECT_EQ(ret, output);
};

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
