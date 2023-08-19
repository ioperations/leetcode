// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You have a browser of one tab where you start on the homepage and you can
visit another url, get back in the history number of steps or move forward in
the history number of steps.

Implement the BrowserHistory class:

BrowserHistory(string homepage) Initializes the object with the homepage of the
browser. void visit(string url) Visits url from the current page. It clears up
all the forward history. string back(int steps) Move steps back in history. If
you can only return x steps in the history and steps > x, you will return only x
steps. Return the current url after moving back in history at most steps.
string forward(int steps) Move steps forward in history. If you can only forward
x steps in the history and steps > x, you will forward only x steps. Return the
current url after forwarding in history at most steps.*/

#include <list>
#include <string>

using namespace std;

namespace { 
class BrowserHistory {
    /*
        1 <= homepage.length <= 20
        1 <= url.length <= 20
        1 <= steps <= 100
        homepage and url consist of  '.' or lower case English letters.
        At most 5000 calls will be made to visit, back, and forward.
    */
   public:
    struct Node {
        string url;
        Node *prev, *next;
        Node(string str) : url(str), prev(nullptr), next(nullptr) {}
    };

    Node *home_page, *curr_page;

    void DeleteNode(Node *head) {
        if (head == nullptr) {
            return;
        }
        DeleteNode(head->next);
        delete head;
    }

   public:
    ~BrowserHistory() { DeleteNode(home_page); }
    BrowserHistory(string homepage) {
        home_page = new Node(homepage);
        curr_page = home_page;
    }

    void Visit(string url) {
        Node *new_page = new Node(url);
        Node *zz = nullptr;
        if (curr_page->next) {
            DeleteNode(curr_page->next);
        }
        curr_page->next = new_page;
        new_page->prev = curr_page;
        curr_page = new_page;
        //       if (zz) {
        //           zz->prev = new_page;
        //           new_page->next = zz;
        //       }
    }

    string Back(int steps) {
        int cnt = 0;
        while (curr_page->prev) {
            curr_page = curr_page->prev;
            cnt++;
            if (cnt == steps) return curr_page->url;
        }
        return curr_page->url;
    }

    string Forward(int steps) {
        int cnt = 0;
        while (curr_page->next) {
            curr_page = curr_page->next;
            cnt++;
            if (cnt == steps) return curr_page->url;
        }
        return curr_page->url;
    }
};
} 

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    // Explanation:
    BrowserHistory *browser_history = new BrowserHistory("leetcode.com");
    // You are in "leetcode.com". Visit "google.com"
    browser_history->Visit("google.com");
    browser_history->Visit("facebook.com");

    auto ret = browser_history->Back(2);
    EXPECT_EQ(ret, "leetcode.com");

    browser_history->Visit("linkedin.com");

    // You are in "linkedin.com", you cannot move forward any steps.
    auto ret1 = browser_history->Forward(2);
    EXPECT_EQ(ret1, "linkedin.com");

    // "google.com". return "google.com"
    auto ret2 = browser_history->Back(2);

    EXPECT_EQ(ret2, "leetcode.com");
    // You are in "google.com", you can move back only one step to
    // "leetcode.com". return "leetcode.com"
    auto ret3 = browser_history->Back(7);

    EXPECT_EQ(ret3, "leetcode.com");
    delete browser_history;
}

TEST(t0, t2) {
    // Input:
    // ["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
    // [["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
    // Output:
    // [null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]

    // Explanation:
    BrowserHistory *browser_history = new BrowserHistory("leetcode.com");
    // You are in "leetcode.com". Visit "google.com"
    browser_history->Visit("google.com");
    // You are in "google.com". Visit "facebook.com"
    browser_history->Visit("facebook.com");
    // You are in "facebook.com". Visit "youtube.com"
    browser_history->Visit("youtube.com");
    // You are in "youtube.com", move back to "facebook.com" return
    // "facebook.com"
    auto ret = browser_history->Back(1);
    EXPECT_EQ(ret, "facebook.com");

    // You are in "facebook.com", move back to "google.com" return "google.com"
    auto ret1 = browser_history->Back(1);
    EXPECT_EQ(ret1, "google.com");

    // You are in "google.com", move forward to "facebook.com" return
    // "facebook.com"
    auto ret2 = browser_history->Forward(1);

    EXPECT_EQ(ret2, "facebook.com");

    // You are in "facebook.com". Visit "linkedin.com"
    browser_history->Visit("linkedin.com");

    // You are in "linkedin.com", you cannot move forward any steps.
    auto ret3 = browser_history->Forward(2);
    // You are in "linkedin.com", move back two steps to "facebook.com" then to
    // "google.com". return "google.com"
    auto ret4 = browser_history->Back(2);

    EXPECT_EQ(ret4, "google.com");
    // You are in "google.com", you can move back only one step to
    // "leetcode.com". return "leetcode.com"
    auto ret5 = browser_history->Back(7);

    EXPECT_EQ(ret5, "leetcode.com");
    delete browser_history;
}

}
