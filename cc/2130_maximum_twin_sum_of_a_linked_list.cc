/*
 * In a linked list of size n, where n is even, the ith node (0-indexed) of the
 * linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2)
 * - 1.
 *
 * For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the
 * twin of node 2. These are the only nodes with twins for n = 4. The twin sum
 * is defined as the sum of a node and its twin.
 *
 * Given the head of a linked list with even length, return the maximum twin sum
 * of the linked list.
 *
 *  The number of nodes in the list is an even integer in the range [2, 105].
 *  1 <= Node.val <= 105
 *
 */

#include <limits>
#include <vector>

#include "datastruct_base.hh"
using ListNode = List::ListNode<int>;

using namespace std;
namespace {
class Solution {
   public:
    int PairSum(ListNode* head) {
        int count = 0;
        ListNode* n = head;
        while (n) {
            count++;
            n = n->next;
        }
        std::vector<int> v;
        v.reserve(count);
        n = head;
        while (n) {
            v.push_back(n->val);
            n = n->next;
        }

        int m = std::numeric_limits<int>::min();
        for (int i = 0; i <= count / 2; i++) {
            m = std::max(v[i] + v[count - 1 - i], m);
        }
        return m;
    }
};

}  // namespace

#include <gtest/gtest.h>

TEST(pairSum, t0) {
    vector<int> head = {5, 4, 2, 1};
    ListNode* n = List::ConstructList(head);

    int output = 6;
    Solution sl;
    int ret = sl.PairSum(n);
    EXPECT_EQ(output, ret);
    List::FreeList(n);
    /*
     * Explanation:
     * Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin
     * sum = 6. There are no other nodes with twins in the linked list. Thus,
     * the maximum twin sum of the linked list is 6.
     */
}
TEST(pairSum, t1) {
    vector<int> head = {4, 2, 2, 3};
    ListNode* n = List::ConstructList(head);

    int output = 7;
    Solution sl;
    int ret = sl.PairSum(n);
    EXPECT_EQ(output, ret);
    List::FreeList(n);
    /*
     * Explanation:
     * The nodes with twins present in this linked list are:
     * - Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
     * - Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
     * Thus, the maximum twin sum of the linked list is max(7, 4) = 7.
     */
}
TEST(pairSum, t2) {
    vector<int> head = {1, 100000};
    ListNode* n = List::ConstructList(head);

    int output = 100001;
    Solution sl;
    int ret = sl.PairSum(n);
    EXPECT_EQ(output, ret);
    List::FreeList(n);
    /*
     * Explanation:
     * There is only one node with a twin in the linked list having twin sum of
     * 1 + 100000 = 100001.
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
