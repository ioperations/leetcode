/*Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).
Implement the MyQueue class:
void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:
You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.*/

use std::collections::VecDeque;
#[allow(unused)]
struct MyQueue {
    innner: VecDeque<i32>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MyQueue {
    #[allow(unused)]
    fn new() -> Self {
        Self {
            innner: VecDeque::new(),
        }
    }

    #[allow(unused)]
    fn push(&mut self, x: i32) {
        self.innner.push_back(x);
    }

    #[allow(unused)]
    fn pop(&mut self) -> i32 {
        self.innner.pop_front().unwrap()
    }

    #[allow(unused)]
    fn peek(&self) -> i32 {
        *self.innner.front().unwrap()
    }

    #[allow(unused)]
    fn empty(&self) -> bool {
        self.innner.len() == 0
    }
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * let obj = MyQueue::new();
 * obj.push(x);
 * let ret_2: i32 = obj.pop();
 * let ret_3: i32 = obj.peek();
 * let ret_4: bool = obj.empty();
 */

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let mut obj = MyQueue::new();
        obj.push(1);
        obj.push(2);
        let ret = obj.peek();
        assert_eq!(ret, 1);
        let ret = obj.pop();
        assert_eq!(ret, 1);
        assert_eq!(obj.empty(), false);
    }
}
