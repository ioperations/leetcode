// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an array of strings words and a width maxWidth, format the text such that
each line has exactly maxWidth characters and is fully (left and right)
justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line does not divide evenly between words, the empty slots
on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified and no extra space is
inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters
only. Each word's length is guaranteed to be greater than 0 and not exceed
maxWidth. The input array words contains at least one word.
*/

#include <queue>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<string> FullJustify(vector<string>& words, int max_width) {
        // int i = 0;

        vector<string> ret;
        std::queue<std::string> q;

        int size = 0;
        for (const auto& ptr : words) {
        retry:
            int const remain_size = max_width - size -
                                    (q.size() ? (q.size() - 1) : 0) -
                                    ((size) ? 1 : 0);

            if (remain_size >= (int)ptr.size()) {
                q.push(ptr);
                size += ptr.size();
            } else {
                std::string str = BuildMaxLeft(q, max_width - size);
                if ((int)str.size() < max_width) {
                    for (int i = (int)str.size(); i < max_width; i++) {
                        str += " ";
                    }
                }

                ret.push_back(str);
                size = 0;
                goto retry;
            }
        }

        if (q.size()) {
            std::string str = BuildAliagnToLeft(q);
            if ((int)str.size() < max_width) {
                for (int i = (int)str.size(); i < max_width; i++) {
                    str += " ";
                }
            }
            ret.push_back(str);
        }

        return ret;
    }
    std::string BuildMaxLeft(std::queue<std::string>& q, int space_size) {
        std::string ret;

        std::vector<int> z = SaperateEvenly(space_size, q.size() - 1);

        int i = 0;
        while (q.size()) {
            std::string const str = q.front();
            ret += str;
            q.pop();
            if (q.size()) {
                for (int j = 0; j < z[i]; j++) {
                    ret += ' ';
                }
            }
            i++;
        }
        // remain should be seprated even to first (q.size() - 1)

        return ret;
    }

    std::string BuildAliagnToLeft(std::queue<std::string>& q) {
        std::string ret;
        while (q.size()) {
            auto tmp = q.front();
            ret += tmp;
            q.pop();
            if (q.size()) {
                ret += ' ';
            }
        }
        return ret;
    }

    // 将一个数字分成size份，分的数据应该满足最大的平均，
    // 多余的份数应该在前size-1份又尽量的平均
    std::vector<int> SaperateEvenly(int num, int size) {
        std::vector<int> ret;
        ret.resize(size);

        int count = 0;
        for (int i = 0; i < size; i++) {
            ret[i]++;
            if (count + 1 == num) {
                break;
            }
            count++;
            if (i + 1 == size) {
                i = -1;
            }
        }
        return ret;
    }
};

TEST(test, t0) {
    Solution s;
    auto ret = s.SaperateEvenly(11, 3);

    EXPECT_EQ(ret, (std::vector<int>{4, 4, 3}));
}

TEST(test, t1) {
    Solution s;
    std::queue<std::string> q;
    q.emplace("hello");
    q.emplace("world");
    q.emplace("i");
    auto ret = s.BuildAliagnToLeft(q);

    EXPECT_EQ(ret, "hello world i");
}

TEST(test, t2) {
    Solution s;
    std::queue<std::string> q;
    q.emplace("hello");
    q.emplace("world");
    q.emplace("i");
    auto ret = s.BuildMaxLeft(q, 5);

    EXPECT_EQ(ret, "hello   world  i");
}
TEST(text_justification, t1) {
    vector<string> words = {
        "This", "is", "an", "example", "of", "text", "justification."};
    int const max_width = 16;
    vector<string> const expected{"This    is    an", "example  of text",
                                  "justification.  "};

    Solution s;
    auto ret = s.FullJustify(words, max_width);
    EXPECT_EQ(ret, expected);
}

TEST(text_justification, t2) {
    vector<string> words = {"What",           "must",  "be",
                            "acknowledgment", "shall", "be"};
    vector<string> const expected = {"What   must   be", "acknowledgment  ",
                                     "shall be        "};
    int const max_width = 16;

    Solution s;
    auto ret = s.FullJustify(words, max_width);
    EXPECT_EQ(ret, expected);
}

TEST(text_justification, t3) {
    vector<string> words =

        {"Science", "is", "what",       "we",   "understand", "well",
         "enough",  "to", "explain",    "to",   "a",          "computer.",
         "Art",     "is", "everything", "else", "we",         "do"};

    vector<string> const expected = {
        "Science  is  what we", "understand      well", "enough to explain to",
        "a  computer.  Art is", "everything  else  we", "do                  "};
    int const max_width = 20;

    Solution s;
    auto ret = s.FullJustify(words, max_width);
    EXPECT_EQ(ret, expected);
}

TEST(text_justification, t4) {
    vector<string> words = {"Listen", "to", "many,", "speak",
                            "to",     "a",  "few."};

    vector<string> const expected = {"Listen", "to    ", "many, ",
                                     "speak ", "to   a", "few.  "};
    int const max_width = 6;

    Solution s;
    auto ret = s.FullJustify(words, max_width);
    EXPECT_EQ(ret, expected);
}

}  // namespace
