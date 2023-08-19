// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Implement a last-in-first-out (LIFO) stack using only two queues. The
implemented stack should support all the functions of a normal stack (push, top,
pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.
Notes:

You must use only standard operations of a queue, which means that only push to
back, peek/pop from front, size and is empty operations are valid. Depending on
your language, the queue may not be supported natively. You may simulate a queue
using a list or deque (double-ended queue) as long as you use only a queue's
standard operations.

You must use only standard operations of a queue, which means that only push to
back, peek/pop from front, size and is empty operations are valid. Depending on
your language, the queue may not be supported natively. You may simulate a queue
using a list or deque (double-ended queue) as long as you use only a queue's
standard operations.
*/

#include <queue>

namespace { 
class MyStack {
    std::queue<int> q;

   public:
    MyStack() {}

    void Push(int x) {
        q.push(x);
        for (int i = 0; i < (int)q.size() - 1; i++) {
            q.push(Pop());
        }
    }
    int Pop() {
        int result = Top();
        q.pop();
        return result;
    }

    int Top() { return q.front(); }

    bool Empty() { return q.empty(); }
};
} 

namespace { 
class MyStackV2 {
   public:
    std::queue<int> q;
    MyStackV2() {}

    void Push(int x) {
        q.push(x);
        int i = 1;
        while (i < (int)q.size()) {
            q.push(q.front());
            q.pop();
            i++;
        }
    }

    int Pop() {
        int ele = q.front();
        q.pop();
        return ele;
    }

    int Top() { return q.front(); }

    bool Empty() { return q.empty(); }
};
} 
#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    // * Your MyStack object will be instantiated and called as such:
    MyStack *obj = new MyStack();
    int x = 0;
    obj->Push(x);
    int param_3 = obj->Top();

    EXPECT_EQ(param_3, x);
    int param_2 = obj->Pop();
    EXPECT_EQ(param_2, x);
    bool param_4 = obj->Empty();
    EXPECT_EQ(param_4, true);

    delete obj;
}

TEST(t1, t1) {
    // * Your MyStack object will be instantiated and called as such:
    MyStackV2 *obj = new MyStackV2();
    int x = 0;
    obj->Push(x);
    int param_3 = obj->Top();

    EXPECT_EQ(param_3, x);
    int param_2 = obj->Pop();
    EXPECT_EQ(param_2, x);
    bool param_4 = obj->Empty();
    EXPECT_EQ(param_4, true);

    delete obj;
}

TEST(t0, t2) {
    // * Your MyStack object will be instantiated and called as such:

    // ["MyStack", "push", "push", "top", "pop", "empty"]
    // [[], [1], [2], [], [], []]
    // Output [null, null, null, 2, 2, false]

    // Explanation
    MyStack *my_stack = new MyStack();
    my_stack->Push(1);
    my_stack->Push(2);

    int ret = my_stack->Top();  // return 2
    EXPECT_EQ(ret, 2);
    ret = my_stack->Pop();  // return 2
    EXPECT_EQ(ret, 2);
    bool ret2 = my_stack->Empty();  // return False
    EXPECT_EQ(ret2, false);

    delete my_stack;
}

TEST(t1, t2) {
    // * Your MyStack object will be instantiated and called as such:

    // ["MyStack", "push", "push", "top", "pop", "empty"]
    // [[], [1], [2], [], [], []]
    // Output [null, null, null, 2, 2, false]

    // Explanation
    MyStackV2 *my_stack = new MyStackV2();
    my_stack->Push(1);
    my_stack->Push(2);

    int ret = my_stack->Top();  // return 2
    EXPECT_EQ(ret, 2);
    ret = my_stack->Pop();  // return 2
    EXPECT_EQ(ret, 2);
    bool ret2 = my_stack->Empty();  // return False
    EXPECT_EQ(ret2, false);

    delete my_stack;
}

}
