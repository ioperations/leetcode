// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given a nested list of integers nestedList. Each element is either an
integer or a list whose elements may also be integers or other lists. Implement
an iterator to flatten it.

Implement the NestedIterator class:

NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the
nested list nestedList. int next() Returns the next integer in the nested list.
boolean hasNext() Returns true if there are still some integers in the nested
list and false otherwise. Your code will be tested with the following
pseudocode:

initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
    If res matches the expected flattened list, then your code will be judged as
correct.
*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation

namespace {
class NestedInteger {
  bool is_integer{};
  int val{};
  vector<NestedInteger> m_vec;

 public:
  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  NestedInteger(vector<int> in) {}
  NestedInteger() = default;
  NestedInteger(int i) : is_integer(true), val(i) {}
  ~NestedInteger() { m_vec.clear(); }

  void AddNestedInteger(NestedInteger& in) {
    is_integer = false;
    m_vec.push_back(in);
    }

    [[nodiscard]] bool IsInteger() const { return is_integer; }

    // Return the single integer that this NestedInteger holds, if it holds a
    // single integer The result is undefined if this NestedInteger holds a
    // nested list
    [[nodiscard]] int GetInteger() const { return val; };

    // Return the nested list that this NestedInteger holds, if it holds a
    // nested list The result is undefined if this NestedInteger holds a single
    // integer const
    vector<NestedInteger>& GetList() { return m_vec; };
};

class NestedIterator {
    int i;
    vector<int> m_faltterned;

    void FlatternAdd(vector<int>& dest, NestedInteger& now) {
        if (now.IsInteger()) {
            dest.push_back(now.GetInteger());
        }

        else {
            for (auto& ptr : now.GetList()) {
                FlatternAdd(dest, ptr);
            }
        }
    }

   public:
    NestedIterator(vector<NestedInteger>& nested_list) : i(0) {
      for (auto& ptr : nested_list) {
        FlatternAdd(m_faltterned, ptr);
      }
    }
    NestedIterator(NestedInteger& nested_list) : i(0) {
      FlatternAdd(m_faltterned, nested_list);
    }

    int next() { return m_faltterned[i++]; }

    bool hasNext() { return i < (int)m_faltterned.size(); }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

TEST(flatten_nested_list_iterator, t1) {
    // vector<NestedInteger> nestedList = {{1,1},2,{1,1}};

    NestedInteger i1(1);
    NestedInteger n1;
    n1.AddNestedInteger(i1);
    n1.AddNestedInteger(i1);

    NestedInteger n;

    n.AddNestedInteger(n1);

    NestedInteger i2(2);
    n.AddNestedInteger(i2);
    n.AddNestedInteger(n1);
    EXPECT_EQ(n.IsInteger(), false);
    EXPECT_EQ(n.GetList().size(), 3);
};

TEST(flatten_nested_list_iterator, t2) {
    // vector<NestedInteger> nestedList = {{1,1},2,{1,1}};

    NestedInteger i1(1);
    NestedInteger n1;
    n1.AddNestedInteger(i1);
    n1.AddNestedInteger(i1);

    NestedInteger n;

    n.AddNestedInteger(n1);

    NestedInteger i2(2);
    n.AddNestedInteger(i2);
    n.AddNestedInteger(n1);

    const vector<int> output = {1, 1, 2, 1, 1};
    // Explanation: By calling next repeatedly until hasNext returns false, the
    // order of elements returned by next should be: [1,1,2,1,1].
    std::vector<int> v;
    // vector<NestedInteger> integer;

    NestedIterator i(n);

    while (i.hasNext()) {
        v.push_back(i.next());
    }
    EXPECT_EQ(v, output);
}

}  // namespace
