/* * Definition for singly-linked list. */

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode *AddTwoNumbers(ListNode *l1, ListNode *l2) {
        for (int i = 0; l1 || l2 || carrier; i++) {
            int va = 0;
            if (l1 && l2) {
                va = l1->val + carrier + l2->val;
            } else if (l1) {
                va = l1->val + carrier;
            } else if (l2) {
                va = l2->val + carrier;
            } else if (carrier) {
                va = carrier;
            }
            carrier = va >= 10 ? 1 : 0;
            va = va % 10;
            ListNode *n = new ListNode(va);
            // 保存 head
            if (i == 0) {
                head = n;
            }

            // 链接节点
            if (i != 0) {
                pre->next = n;
            }

            // 前一个节点
            pre = n;

            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }

        return head;
    }

   private:
    mutable int carrier = 0;
    ListNode *head = nullptr;
    ListNode *pre = nullptr;
    /*

      n -> n1 -> n2 -> n3

        * first free list n1 ; then free n
            * first free list n2 ; then free n1
                * first free list n3 ; then free n2

    */
   public:
    void FreeListNode(ListNode *n) {
        if (!n) {
            return;
        }

        FreeListNode(n->next);
        std::cout << " free: " << n->val;
        delete n;
    }
};

void PrintNode(ListNode *n) {
    std::cout << std::endl;

    for (; n;) {
        std::cout << n->val << " -> ";
        n = n->next;
    }
    std::cout << std::endl;
}

int main() {
    Solution s;

    // construct two nodes

    ListNode l1(2);
    ListNode l1_1(4);
    ListNode l1_2(3);
    ListNode l1_3(3);

    {
        l1.next = &l1_1;
        l1_1.next = &l1_2;
        /* l1_2.next = &l1_3; */
    }

    ListNode l2(5);
    ListNode l2_1(6);
    ListNode l2_2(6);
    ListNode l2_3(4);

    {
        l2.next = &l2_1;
        l2_1.next = &l2_2;
        /* l2_2.next = &l2_3; */
    }

    PrintNode(&l1);
    PrintNode(&l2);

    {
        ListNode *t1 = new ListNode(2);
        ListNode *t1_1 = new ListNode(4);
        ListNode *t1_2 = new ListNode(3);
        ListNode *t1_3 = new ListNode(5);
        ListNode *t1_4 = new ListNode(9);
        t1->next = t1_1;
        t1_1->next = t1_2;
        t1_2->next = t1_3;
        t1_3->next = t1_4;
        PrintNode(t1);
        s.FreeListNode(t1);
    }

    ListNode *ret = s.AddTwoNumbers(&l1, &l2);

    PrintNode(ret);
    s.FreeListNode(ret);

    std::cout << std::endl;
    (void)ret;
    return 0;
}
