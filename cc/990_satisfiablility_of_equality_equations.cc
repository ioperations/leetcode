// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an array of strings equations that represent relationships between
variables where each string equations[i] is of length 4 and takes one of two
different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not
necessarily different) that represent one-letter variable names.

Return true if it is possible to assign integers to variable names so as to
satisfy all the given equations, or false otherwise.*/
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class DSU {
   public:
    DSU() { MakeSet(); }
    DSU(const DSU&) = default;
    DSU(DSU&&) = default;
    DSU& operator=(const DSU&) = default;
    DSU& operator=(DSU&&) = default;
    ~DSU() = default;

    void MakeSet() {
        for (int i = 0; i < 26; i++) {
            m_parent.at(i) = i;
            m_rank.at(i) = 0;
        }
    }

    int FindParent(int x) {
        if (m_parent.at(x) != x) {
            m_parent.at(x) = FindParent(m_parent.at(x));
        }
        return m_parent.at(x);
    }

    void Unionn(int x, int y) {
        int const u = FindParent(x);
        int const v = FindParent(y);
        if (u == v) {
            return;
        }
        if (m_rank.at(u) < m_rank.at(v)) {
            m_parent.at(u) = v;
        } else if (m_rank.at(u) > m_rank.at(v)) {
            m_parent.at(v) = u;
        } else {
            m_parent.at(u) = v;
            m_rank.at(u) = m_rank.at(v) + 1;
        }
    }

   private:
    std::array<int, 26> m_rank{};
    std::array<int, 26> m_parent{};
};

class Solution {
   public:
    bool EquationsPossible(vector<string>& equations) {
        DSU obj;
        for (const auto& it : equations) {
            // first unify all the elements which are equal
            if (it.at(1) == '=') {
                int const x = it.at(0) - 'a';
                int const y = it.at(3) - 'a';
                obj.Unionn(x, y);
            }
        }
        for (const auto& it : equations) {
            // Find parents, if they are equal means we can't give them
            // different numbers, so return false.
            if (it.at(1) == '!') {
                int const x = obj.FindParent(it.at(0) - 'a');
                int const y = obj.FindParent(it.at(3) - 'a');
                if (x == y) {
                    return false;
                }
            }
        }
        return true;
    }
};

TEST(SatisfiablilityOfEqualityEquations, t1) {
    vector<string> equations = {"a==b", "b!=a"};
    bool const output = false;
    // Explanation: If we assign say, a = 1 and b = 1, then the first equation
    // is satisfied, but not the second.
    // There is no way to assign the variables to satisfy both equations.
    Solution sl;
    bool const ret = sl.EquationsPossible(equations);
    EXPECT_EQ(ret, output);
}

TEST(SatisfiablilityOfEqualityEquations, t2) {
    vector<string> equations = {"b==a", "a==b"};
    bool const output = true;
    // Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

    Solution sl;
    bool const ret = sl.EquationsPossible(equations);
    EXPECT_EQ(ret, output);
}
}  // namespace
