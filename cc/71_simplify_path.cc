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

#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    [[nodiscard]] std::string SimplifyPath(std::string path) const {
        std::stack<std::string> st;
        std::string res;

        for (size_t i = 0; i < path.size(); ++i) {
            if (path.at(i) == '/') continue;
            std::string temp;
            while (i < path.size() && path.at(i) != '/') {
                temp += path.at(i);
                ++i;
            }
            if (temp == ".") continue;
            if (temp == "..") {
                if (!st.empty()) {
                    st.pop();
                }
            } else {
                st.push(temp);
            }
        }

        while (!st.empty()) {
            res = "/" + st.top() + res;
            st.pop();
        }

        if (res.size() == 0) return "/";

        return res;
    }
};

class SolutionV2 {
   public:
    SolutionV2() = default;
    virtual ~SolutionV2() = default;

    std::stack<string> m_stack;
    [[nodiscard]] std::string SimplifyPath(std::string path) {
        std::string ret;

        replace(path.begin(), path.end(), '/', ' ');

        std::stringstream ss(path);

        std::string tmp;
        while (ss >> tmp) {
            if (tmp == "..") {
                if (m_stack.size()) m_stack.pop();
            } else if (tmp == ".") {
            } else {
                m_stack.push(tmp);
            }
        }

        while (m_stack.size()) {
            ret = ('/' + m_stack.top()) + ret;
            m_stack.pop();
        }
        if (ret == "") {
            return "/";
        }
        return ret;
    }
};

TEST(simplifyV, t1) {
    std::string const path = "/home/";
    std::string const output = "/home";
    // Explanation : Note that there is no trailing slash after the last
    // directory name.*

    Solution const s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplifyV, t2) {
    std::string const path = "/../";
    std::string const output = "/";
    // Explanation: Going one level up from the root directory is a no-op, as
    // the root level is the highest level you can go.
    Solution const s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplifyV, t3) {
    std::string const path = "/home//foo/";
    std::string const output = "/home/foo";
    // Explanation: In the canonical path, multiple consecutive slashes are
    // replaced by a single one.
    Solution const s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplifypathV2, t1) {
    std::string const path = "/home/";
    std::string const output = "/home";
    // Explanation : Note that there is no trailing slash after the last
    // directory name.*

    SolutionV2 s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplifypathV2, t2) {
    std::string const path = "/../";
    std::string const output = "/";
    // Explanation: Going one level up from the root directory is a no-op, as
    // the root level is the highest level you can go.
    SolutionV2 s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}

TEST(simplifypathV2, t3) {
    std::string const path = "/home//foo/";
    std::string const output = "/home/foo";
    // Explanation: In the canonical path, multiple consecutive slashes are
    // replaced by a single one.
    SolutionV2 s;
    auto ret = s.SimplifyPath(path);
    EXPECT_EQ(ret, output);
}
}  // namespace
