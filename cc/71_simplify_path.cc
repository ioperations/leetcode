// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string path, which is an absolute path (starting with a slash '/') to a
file or directory in a Unix-style file system, convert it to the simplified
canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a
double period '..' refers to the directory up a level, and any multiple
consecutive slashes (i.e. '//') are treated as a single slash '/'. For this
problem, any other format of periods such as '...' are treated as file/directory
names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to
the target file or directory (i.e., no period '.' or double period '..') Return
the simplified canonical path.
*/

#include <stddef.h>

#include <algorithm>
#include <sstream>
#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string SimplifyPath(string path) {
        // pass
        stack<string> st;
        string res;

        for (size_t i = 0; i < path.size(); ++i) {
            if (path[i] == '/') continue;
            string temp;
            // iterate till we doesn't traverse the whole string and doesn't
            // encounter the last /
            while (i < path.size() && path[i] != '/') {
                // add path to temp string
                temp += path[i];
                ++i;
            }
            if (temp == ".") continue;
            // pop the top element from stack if exists
            if (temp == "..") {
                if (!st.empty()) st.pop();
            } else
                // push the directory file name to stack
                st.push(temp);
        }

        // adding all the stack elements to res
        while (!st.empty()) {
            res = "/" + st.top() + res;
            st.pop();
        }

        // if no directory or file is present
        if (res.size() == 0) return "/";

        return res;
    }
};

class SolutionV2 {
   public:
    SolutionV2(){};
    virtual ~SolutionV2(){};

    std::stack<string> stack;
    string SimplifyPath(string path) {
        string ret;

        replace(path.begin(), path.end(), '/', ' ');

        stringstream ss(path);

        string tmp;
        while (ss >> tmp) {
            if (tmp == "..") {
                if (stack.size()) stack.pop();
            } else if (tmp == ".") {
            } else {
                stack.push(tmp);
            }
        }

        while (stack.size()) {
            ret = ('/' + stack.top()) + ret;
            stack.pop();
        }
        if (ret == "") {
            return "/";
        }
        return ret;
    }
};

TEST(simplify_path, t1) {
    std::string path = "/home/";
    std::string output = "/home";
    // Explanation : Note that there is no trailing slash after the last
    // directory name.*

    Solution s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplify_path, t2) {
    std::string path = "/../";
    std::string output = "/";
    // Explanation: Going one level up from the root directory is a no-op, as
    // the root level is the highest level you can go.
    Solution s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplify_path, t3) {
    std::string path = "/home//foo/";
    std::string output = "/home/foo";
    // Explanation: In the canonical path, multiple consecutive slashes are
    // replaced by a single one.
    Solution s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(t1, t1) {
    std::string path = "/home/";
    std::string output = "/home";
    // Explanation : Note that there is no trailing slash after the last
    // directory name.*

    SolutionV2 s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(t1, t2) {
    std::string path = "/../";
    std::string output = "/";
    // Explanation: Going one level up from the root directory is a no-op, as
    // the root level is the highest level you can go.
    SolutionV2 s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(t1, t3) {
    std::string path = "/home//foo/";
    std::string output = "/home/foo";
    // Explanation: In the canonical path, multiple consecutive slashes are
    // replaced by a single one.
    SolutionV2 s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}
}  // namespace
