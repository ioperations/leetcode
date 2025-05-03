// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    Design an iterator that supports the peek operation on an existing iterator
   in addition to the hasNext and the next operations.

    Implement the PeekingIterator class:

    PeekingIterator(Iterator<int> nums) Initializes the object with the given
    integer iterator iterator. int next() Returns the next element in the array
   and moves the pointer to the next element. boolean hasNext() Returns true if
   there are still elements in the array. int peek() Returns the next element in
   the array without moving the pointer. Note: Each language may have a
   different implementation of the constructor and Iterator, but they all
   support the int next() and boolean hasNext() functions.
*/

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 */

#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Iterator {
    const std::vector<int>& m_nums;
    int size;
    int i{-1};

   public:
    Iterator(const vector<int>& nums) : m_nums(nums), size(nums.size()) {}

    Iterator(const Iterator& iter) = default;

    // Returns the next element in the iteration.
    int next() {
        if (!hasNext()) {
            return -1;
        }
        i++;
        return m_nums[i];
    };

    // Returns true if the iteration has more elements.
    [[nodiscard]] bool hasNext() const {
        return 0 <= (i + 1) && (i + 1) < size;
    };
};

class PeekingIterator : public Iterator {
  int m_next_val;

 public:
  PeekingIterator(const vector<int>& nums)
      : Iterator(nums), m_next_val(Iterator::next()) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
  }

    // Returns the next element in the iteration without advancing the iterator.
    int Peek() { return m_next_val; }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
      int const temp = m_next_val;
      if (Iterator::hasNext())
        m_next_val = Iterator::next();
      else
        m_next_val = 0;
      return temp;
    }

    [[nodiscard]] bool hasNext() const { return (m_next_val != 0); }
};

TEST(peeking_iterator, t1) {
    // Input ["PeekingIterator", "next", "peek", "next", "next", "hasNext"]
    // [[[1, 2, 3]], [], [], [], [], []]
    // Output [null, 1, 2, 2, 3, false]

    // Explanation
    std::vector<int> const z{1, 2, 3};
    auto* peeking_iterator = new Iterator(z);
    // [1,2,3]

    // return 1, the pointer moves to the next element [1,2,3].
    auto ret = peeking_iterator->next();
    EXPECT_EQ(ret, 1);

    // return 2, the pointer moves to the next element [1,2,3]
    ret = peeking_iterator->next();
    EXPECT_EQ(ret, 2);

    // return 3, the pointer moves to the next element [1,2,3]
    ret = peeking_iterator->next();
    EXPECT_EQ(ret, 3);

    bool const ret2 = peeking_iterator->hasNext();  // return False}
    EXPECT_EQ(ret2, false);

    delete peeking_iterator;
}

TEST(peeking_iterator, t2) {
    // Input ["PeekingIterator", "next", "peek", "next", "next", "hasNext"]
    // [[[1, 2, 3]], [], [], [], [], []]
    // Output [null, 1, 2, 2, 3, false]

    // Explanation
    std::vector<int> const z{1, 2, 3};
    auto* peeking_iterator = new PeekingIterator(z);
    // [1,2,3]

    // return 1, the pointer moves to the next element [1,2,3].
    auto ret = peeking_iterator->next();
    EXPECT_EQ(ret, 1);

    // return 2, the pointer does not move [1,2,3].
    ret = peeking_iterator->Peek();
    EXPECT_EQ(ret, 2);

    // return 2, the pointer moves to the next element [1,2,3]
    ret = peeking_iterator->next();
    EXPECT_EQ(ret, 2);

    // return 3, the pointer moves to the next element [1,2,3]
    ret = peeking_iterator->next();
    EXPECT_EQ(ret, 3);

    bool const ret2 = peeking_iterator->hasNext();  // return False}
    EXPECT_EQ(ret2, false);

    delete peeking_iterator;
}

}  // namespace
