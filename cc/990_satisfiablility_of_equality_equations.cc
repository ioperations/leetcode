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
    int rank[26], parent[26];
    DSU() { MakeSet(); }

    void MakeSet() {
        for (int i = 0; i < 26; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int FindParent(int x) {
        if (parent[x] != x) {
            parent[x] = FindParent(parent[x]);
        }
        return parent[x];
    }

    void Unionn(int x, int y) {
        int const u = FindParent(x);
        int const v = FindParent(y);
        if (u == v) {
            return;
        }
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[u] = v;
            rank[u] = rank[v] + 1;
        }
    }
    ~DSU() = default;
};

class Solution {
   public:
    bool EquationsPossible(vector<string> &equations) {
        DSU obj;
        for (const auto &it : equations) {
            // first unify all the elements which are equal
            if (it[1] == '=') {
                int const x = it[0] - 'a';
                int const y = it[3] - 'a';
                obj.Unionn(x, y);
            }
        }
        for (const auto &it : equations) {
            // Find parents, if they are equal means we can't give them
            // different numbers, so return false.
            if (it[1] == '!') {
                int const x = obj.FindParent(it[0] - 'a');
                int const y = obj.FindParent(it[3] - 'a');
                if (x == y) {
                    return false;
                }
            }
        }
        return true;
    }
};

TEST(satisfiablility_of_equality_equations, t1) {
    vector<string> equations = {"a==b", "b!=a"};
    bool const output = false;
    // Explanation: If we assign say, a = 1 and b = 1, then the first equation
    // is satisfied, but not the second.
    // There is no way to assign the variables to satisfy both equations.
    Solution sl;
    bool const ret = sl.EquationsPossible(equations);
    EXPECT_EQ(ret, output);
}

TEST(satisfiablility_of_equality_equations, t2) {
    vector<string> equations = {"b==a", "a==b"};
    bool const output = true;
    // Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

    Solution sl;
    bool const ret = sl.EquationsPossible(equations);
    EXPECT_EQ(ret, output);
}
}  // namespace
