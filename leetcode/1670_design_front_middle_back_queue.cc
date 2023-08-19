// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Design a queue that supports push and pop operations in the front, middle, and
back.

Implement the FrontMiddleBack class:

FrontMiddleBack() Initializes the queue.
void pushFront(int val) Adds val to the front of the queue.
void pushMiddle(int val) Adds val to the middle of the queue.
void pushBack(int val) Adds val to the back of the queue.
int popFront() Removes the front element of the queue and returns it. If the
queue is empty, return -1. int popMiddle() Removes the middle element of the
queue and returns it. If the queue is empty, return -1. int popBack() Removes
the back element of the queue and returns it. If the queue is empty, return -1.
Notice that when there are two middle position choices, the operation is
performed on the frontmost middle position choice. For example:

Pushing 6 into the middle of [1, 2, 3, 4, 5] results in [1, 2, 6, 3, 4, 5].
Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in [1, 2, 4, 5,
6].
*/
#include <queue>
#include <stack>
using namespace std;

namespace { 
class FrontMiddleBackQueue {
    deque<int> q;

   public:
    FrontMiddleBackQueue() {}
    ~FrontMiddleBackQueue() { q.clear(); }

    void PushFront(int val) { q.push_front(val); }

    void PushMiddle(int val) {
        deque<int> q1;
        int size = q.size() / 2;
        for (int i = 0; i < size; i++) {
            int val = q.front();
            q.pop_front();
            q1.push_back(val);
        }
        q.push_front(val);
        while (!q1.empty()) {
            int val = q1.back();
            q1.pop_back();
            q.push_front(val);
        }
    }

    void PushBack(int val) { q.push_back(val); }

    int PopFront() {
        if (q.empty()) return -1;
        int val = q.front();
        q.pop_front();
        return val;
    }

    int PopMiddle() {
        int size = q.size();
        if (q.empty() || size < size / 2) return -1;

        if (size % 2 == 0) {
            size = (size / 2) - 1;
        } else {
            size = size / 2;
        }
        deque<int> q1;
        for (int i = 0; i < size; i++) {
            int val = q.front();
            q.pop_front();
            q1.push_back(val);
        }
        int t = q.front();
        q.pop_front();

        while (!q1.empty()) {
            int val = q1.back();
            q1.pop_back();
            q.push_front(val);
        }
        return t;
    }

    int PopBack() {
        if (q.empty()) return -1;
        int val = q.back();
        q.pop_back();
        return val;
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    FrontMiddleBackQueue *q = new FrontMiddleBackQueue();
    q->PushFront(1);          // [1]
    q->PushBack(2);           // [1, 2]
    q->PushMiddle(3);         // [1, 3, 2]
    q->PushMiddle(4);         // [1, 4, 3, 2]
    int ret = q->PopFront();  // return 1 -> [4, 3, 2]
    EXPECT_EQ(ret, 1);
    ret = q->PopMiddle();  // return 3 -> [4, 2]
    EXPECT_EQ(ret, 3);
    ret = q->PopMiddle();  // return 4 -> [2]
    EXPECT_EQ(ret, 4);
    ret = q->PopBack();  // return 2 -> []
    EXPECT_EQ(ret, 2);
    ret = q->PopFront();  // return -1 -> [] (The queue is empty)
    EXPECT_EQ(ret, -1);
    delete q;
}

}
