// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Design your implementation of the circular queue. The circular queue is a
linear data structure in which the operations are performed based on FIFO (First
In First Out) principle and the last position is connected back to the first
position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces
in front of the queue. In a normal queue, once the queue becomes full, we cannot
insert the next element even if there is a space in front of the queue. But
using the circular queue, we can use the space to store new values.

Implementation the MyCircularQueue class:

MyCircularQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return
-1. int Rear() Gets the last item from the queue. If the queue is empty, return
-1. boolean enQueue(int value) Inserts an element into the circular queue.
Return true if the operation is successful. boolean deQueue() Deletes an element
from the circular queue. Return true if the operation is successful. boolean
isEmpty() Checks whether the circular queue is empty or not. boolean isFull()
Checks whether the circular queue is full or not. You must solve the problem
without using the built-in queue data structure in your programming language.

 */

/*
Example 1:

Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear",
"isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]
*/

#include <vector>

#include "gtest/gtest.h"

namespace {
class MyCircularQueue {
   private:
    std::vector<int> m_v;
    int m_start = 0, m_len = 0;

   public:
    MyCircularQueue(int k) : m_v(k) {}
    bool EnQueue(int value) {
        if (IsFull()) return false;
        m_v[(m_start + m_len++) % m_v.size()] = value;
        return true;
    }
    bool DeQueue() {
        if (IsEmpty()) return false;
        m_start = (m_start + 1) % m_v.size();
        --m_len;
        return true;
    }
    int Front() {
        if (IsEmpty()) return -1;
        return m_v[m_start];
    }
    int Rear() {
        if (IsEmpty()) return -1;
        return m_v[(m_start + m_len - 1) % m_v.size()];
    }
    bool IsEmpty() { return !m_len; }
    bool IsFull() { return m_len == (int)m_v.size(); }
};

TEST(design_circular_queue, t1) {
    MyCircularQueue my_circular_queue(3);
    bool ret = my_circular_queue.EnQueue(1);  // return True
    EXPECT_EQ(ret, true);
    ret = my_circular_queue.EnQueue(2);  // return True
    EXPECT_EQ(ret, true);
    ret = my_circular_queue.EnQueue(3);  // return True
    EXPECT_EQ(ret, true);
    ret = my_circular_queue.EnQueue(4);  // return False
    EXPECT_EQ(ret, false);
    int ret1 = my_circular_queue.Rear();  // return 3
    EXPECT_EQ(ret1, 3);
    ret = my_circular_queue.IsFull();  // return True
    EXPECT_EQ(ret, true);
    ret = my_circular_queue.DeQueue();  // return True
    EXPECT_EQ(ret, true);
    ret = my_circular_queue.EnQueue(4);  // return True
    EXPECT_EQ(ret, true);
    ret1 = my_circular_queue.Rear();  // return 4
    EXPECT_EQ(ret1, 4);
}

}  // namespace
