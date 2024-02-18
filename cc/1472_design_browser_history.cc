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

#include <string>

#include "gtest/gtest.h"

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


using namespace std;
class BrowserHistorySysV2 {
   public:
    BrowserHistorySysV2(const string &homepage, int max_count) {
        capability = max_count;
        p_head = new Node("head");
        p_end = new Node("end");
        p_head->next = p_end;
        p_end->pre = p_head;
        p_head->pre = nullptr;
        p_end->next = nullptr;

        struct Node *p = new Node(homepage);
        AddToHead(p);
        p_currnet = p;
        current_size = 1;
    }

    ~BrowserHistorySysV2() {
        Node *p = p_head;
        while (p != nullptr) {
            Node *tmp = p;
            p = p->next;
            delete tmp;
        }
    }

    int Visit(const string &url) {
        if (p_currnet->url == url) {
            return current_size;
        }

        CleanNodeToHead();

        struct Node *p = new Node(url);
        AddToHead(p);
        current_size++;
        p_currnet = p;

        if (current_size > capability) {
            DeleteLastNode();
        }
        return current_size;
    }

    string Back() {
        Node *p = p_currnet;
        if (p->next != p_end) {
            p = p->next;
        }
        p_currnet = p;
        return p->url;
    }

    string Forward() {
        Node *p = p_currnet;
        if (p->pre != p_head) {
            p = p->pre;
        }
        p_currnet = p;
        return p->url;
    }

   private:
    struct Node {
        struct Node *next;
        std::string url;
        struct Node *pre;

        Node(std::string u) {
            url = u;
            next = nullptr;
            pre = nullptr;
        }
    };

    void CleanNodeToHead() {
        Node *p = p_currnet->pre;
        while (p != p_head) {
            Node *tmp = p->pre;
            delete p;
            p = tmp;
            current_size--;
        }

        p = p_currnet;
        p_head->next = p;
        p->pre = p_head;
    }

    void AddToHead(struct Node *n) {
        p_head->next->pre = n;
        n->next = p_head->next;
        n->pre = p_head;
        p_head->next = n;
    }

    void DeleteLastNode() {
        Node *target = p_end->pre;
        target->pre->next = target->next;
        target->next->pre = target->pre;
        delete target;
        current_size--;
    }

    struct Node *p_currnet;
    struct Node *p_head;
    struct Node *p_end;
    int current_size;

    int capability;
};


TEST(t1, t1) {
    BrowserHistorySysV2 br("w3.huawei.com", 10);
    int ret = br.Visit("google.com");
    EXPECT_EQ(2, ret);
    auto r = br.Back();
    EXPECT_EQ("w3.huawei.com", r);
    r = br.Forward();
    EXPECT_EQ("google.com", r);
    r = br.Forward();
    EXPECT_EQ("google.com", r);
    ret = br.Visit("baidu.com");
    EXPECT_EQ(3, ret);
    ret = br.Visit("youtube.com");
    EXPECT_EQ(4, ret);
    r = br.Back();
    EXPECT_EQ("baidu.com", r);
    ret = br.Visit("baidu.com");
    EXPECT_EQ(4, ret);

    r = br.Back();
    EXPECT_EQ("google.com", r);
    ret = br.Visit("mails.huawei.com");
    EXPECT_EQ(3, ret);
}

TEST(t1, t2) {
    BrowserHistorySysV2 br("www.huawei.com", 3);
    int ret = br.Visit("w3.huawei.com");
    EXPECT_EQ(2, ret);
    ret = br.Visit("w4.huawei.com");
    EXPECT_EQ(3, ret);
    auto r = br.Back();
    EXPECT_EQ("w3.huawei.com", r);
    ret = br.Visit("www.huawei.com");
    EXPECT_EQ(3, ret);
    ret = br.Visit("w5.huawei.com");
    EXPECT_EQ(3, ret);

    ret = br.Visit("w6.huawei.com");
    EXPECT_EQ(3, ret);
}

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */


TEST(design_browser_history, t1) {
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

TEST(design_browser_history, t2) {
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

}  // namespace
