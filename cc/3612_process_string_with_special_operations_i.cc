/*
 * You are given a string s consisting of lowercase English letters and the
 * special characters: *, #, and %.
 *
 * Build a new string result by processing s according to the following rules
 * from  left to right:
 *
 * If the letter is a lowercase English letter append it to result.
 * A '*' removes the last character from result, if it exists.
 * A '#' duplicates the current result and appends it to itself.
 * A '%' reverses the current result.
 * Return the final string result after processing all characters in s.
 **/

#include <string>
using namespace std;

namespace {
struct LinkList {
    char v;
    struct LinkList* pre;
    struct LinkList* next;

    LinkList(char v) : v(v), pre(nullptr), next(nullptr) {}
    LinkList() : v(0), pre(nullptr), next(nullptr) {}
    LinkList(char v, LinkList* pre, LinkList* next)
        : v(v), pre(pre), next(next) {}
};

struct DoubleLinkList {
    DoubleLinkList(LinkList* head, LinkList* end) : head(head), end(end) {
        head->next = end;
        end->pre = head;
    }

    void AddToend(char n) {
        auto* current = new LinkList(n);
        LinkList* p = end->pre;

        p->next = current;
        current->next = end;
        end->pre = current;
        current->pre = p;
    }

    void Reverse() {
        if (end->pre == head) {
            return;
        }

        LinkList* current = head->next;

        while (current != end) {
            LinkList* next_node = current->next;  // Save the true next node

            // Swap next and pre pointers for the actual data node
            current->next = current->pre;
            current->pre = next_node;

            current = next_node;  // Advance to the original next node
        }

        // Now, fix the sentinels to point to the newly swapped boundary nodes
        LinkList* first_data_node = end->pre;   // Original last data node
        LinkList* last_data_node = head->next;  // Original first data node

        head->next = first_data_node;
        first_data_node->pre = head;

        end->pre = last_data_node;
        last_data_node->next = end;
    }

    void RemoveLast() {
        if (end->pre == head) {
            return;
        }
        auto* p = end->pre;
        auto* z = p->pre;
        z->next = end;
        end->pre = z;
        delete p;
    }

    void DuplicateCurrent() {
        auto str = BuildString();
        for (auto& c : str) {
            AddToend(c);
        }
    }
    void FreeList() {
        LinkList* p = head->next;

        while (p != end) {
            auto* pp = p;
            p = p->next;
            delete pp;
        }
    }
    std::string BuildString() {
        std::string ret;
        LinkList* p = head->next;
        while (p != end) {
            ret.push_back(p->v);
            p = p->next;
        }
        return ret;
    }

    LinkList* head;
    LinkList* end;
};

class Solution {
   public:
    string ProcessStr(const string& s) {
        LinkList head;
        LinkList end;
        DoubleLinkList double_link_list(&head, &end);

        for (auto& c : s) {
            if (c == '#') {
                double_link_list.DuplicateCurrent();
            } else if (c == '%') {
                double_link_list.Reverse();
            } else if (c == '*') {
                double_link_list.RemoveLast();
            } else {
                double_link_list.AddToend(c);
            }
        }
        auto ss = double_link_list.BuildString();
        double_link_list.FreeList();
        return ss;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(processStr, t1) {
    string s = "a#b%*";

    string output = "ba";
    Solution sl;
    auto ret = sl.ProcessStr(s);
    EXPECT_EQ(output, ret);

    /*
     * Explanation:
     * i	s[i]	Operation	Current result
     * 0	'a'	Append 'a'	"a"
     * 1	'#'	Duplicate result	"aa"
     * 2	'b'	Append 'b'	"aab"
     * 3	'%'	Reverse result	"baa"
     * 4	'*'	Remove the last character	"ba"
     * Thus, the final result is "ba".
     */
}

TEST(processStr, t2) {
    string s = "a#b%*";
    string output = "ba";
    Solution sl;
    auto ret = sl.ProcessStr(s);
    EXPECT_EQ(output, ret);
    /*
     * Explanation:
     * i	s[i]	Operation	Current result
     * 0	'a'	Append 'a'	"a"
     * 1	'#'	Duplicate result	"aa"
     * 2	'b'	Append 'b'	"aab"
     * 3	'%'	Reverse result	"baa"
     * 4	'*'	Remove the last character	"ba"
     * Thus, the final result is "ba".
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
