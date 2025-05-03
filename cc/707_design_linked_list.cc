// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Design your implementation of the linked list. You can choose to use a singly
or doubly linked list. A node in a singly linked list should have two
attributes: val and next. val is the value of the current node, and next is a
pointer/reference to the next node. If you want to use the doubly linked list,
you will need one more attribute prev to indicate the previous node in the
linked list. Assume all nodes in the linked list are 0-indexed.

Implement the MyLinkedList class:

MyLinkedList() Initializes the MyLinkedList object.
int get(int index) Get the value of the indexth node in the linked list. If the
index is invalid, return -1. void addAtHead(int val) Add a node of value val
before the first element of the linked list. After the insertion, the new node
will be the first node of the linked list. void addAtTail(int val) Append a node
of value val as the last element of the linked list. void addAtIndex(int index,
int val) Add a node of value val before the indexth node in the linked list. If
index equals the length of the linked list, the node will be appended to the end
of the linked list. If index is greater than the length, the node will not be
inserted. void deleteAtIndex(int index) Delete the indexth node in the linked
list, if the index is valid.*/

#include "gtest/gtest.h"

namespace {
class Node {
   public:
    int val;
    Node* next;
    Node(int val) : val(val), next(nullptr) {}
};
class MyLinkedList {
    void FreeNode(Node* r) {
        if (r == nullptr) return;
        FreeNode(r->next);
        delete r;
    }

   public:
    int m_size = 0;
    Node* m_head = new Node(0);
    MyLinkedList() = default;

    ~MyLinkedList() { FreeNode(m_head); }
    int Get(int index) {
      if (index < 0 || index >= m_size) return -1;
      Node* temp = m_head->next;
      for (int i = 0; i < index; i++) temp = temp->next;
      return temp->val;
    }
    void AddAtHead(int val) {
      Node* temp = m_head->next;
      m_head->next = new Node(val);
      m_head->next->next = temp;
      m_size++;
    }
    void AddAtTail(int val) {
      Node* temp = m_head;
      while (temp->next != nullptr) temp = temp->next;
      temp->next = new Node(val);
      m_size++;
    }
    void AddAtIndex(int index, int val) {
      if (index > m_size) return;
      Node* temp = m_head;
      for (int i = 0; i < index; i++) temp = temp->next;
      Node* temp1 = temp->next;
      temp->next = new Node(val);
      temp->next->next = temp1;
      m_size++;
    }
    void DeleteAtIndex(int index) {
      if (index < 0 || index >= m_size) return;
      Node* temp = m_head;
      for (int i = 0; i < index; i++) temp = temp->next;
      Node* temp1 = temp->next;
      temp->next = temp1->next;
      temp1->next = nullptr;
      m_size--;
      delete temp1;
    }
};

TEST(design_linked_list, t1) {
  auto* my_linked_list = new MyLinkedList();
  my_linked_list->AddAtHead(1);
  my_linked_list->AddAtTail(3);
  my_linked_list->AddAtIndex(1, 2);  // linked list becomes 1->2->3
  int ret = my_linked_list->Get(1);  // return 2
  EXPECT_EQ(ret, 2);
  my_linked_list->DeleteAtIndex(1);  // now the linked list is 1->3
  ret = my_linked_list->Get(1);      // return 3
  EXPECT_EQ(ret, 3);
  delete my_linked_list;
}

}  // namespace
