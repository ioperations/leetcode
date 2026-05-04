// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
A valid number can be split up into these components (in order):

A decimal number or an integer.
(Optional) An 'e' or 'E', followed by an integer.
A decimal number can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One of the following formats:
One or more digits, followed by a dot '.'.
One or more digits, followed by a dot '.', followed by one or more digits.
A dot '.', followed by one or more digits.
An integer can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One or more digits.
For example, all the following are valid numbers: ["2", "0089", "-0.1", "+3.14",
"4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], while
the following are not valid numbers: ["abc", "1a", "1e", "e3", "99e2.5", "--6",
"-+3", "95a54e53"].

Given a string s, return true if s is a valid number.
*/

#include <cctype>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include <cstddef>

namespace {
class Solution {
   public:
    // recursive descendent parsing? not very strict: losing constraints

    // 0 to 9 sequences
    // a key semantics: each parseX() will just extract a valid X, not checking
    // if it is the last one the caller function should do the check!!

    bool ParseDigits(const string& s, int& i) {
        int j = i;
        while (j < static_cast<int>(s.size()) && isdigit(s.at(j))) j++;
        bool ret = false;
        // j is out of bound or s[j] is not digit anymore
        if (j - i > 0)  // len of digits
        {
            ret = true;
            i = j;
        }
        return ret;
    }

    bool ParseDecimal(const string& s, int& i) {
        if (i == static_cast<int>(s.size())) return false;

        // optionally + or -
        if (s.at(i) == '+' || s.at(i) == '-') i++;

        if (i == static_cast<int>(s.size())) {
            return false;
        }

        if (ParseDigits(s, i)) {
            if (i == static_cast<int>(s.size())) return false;
            if (s.at(i) == '.') {
                i++;
                //  if (i==s.size())  // how to handle 46.e3 ??  conflicting
                //  semantics
                //     return true;
                if (ParseDigits(s, i)) {
                    return true;
                }
                return true;
            }
        } else if (s.at(i) == '.') {
            i++;
            if (ParseDigits(s, i)) return true;  // mistake return i==s.size();
        }

        return false;
    }

    // integer may be a part of the component, followed by more things
    bool ParseInteger(const string& s, int& i) {
        if (i == static_cast<int>(s.size())) return false;
        // optionally + or -
        if (s.at(i) == '+' || s.at(i) == '-') i++;

        if (ParseDigits(s, i)) {
            return true;  // return i==s.size(); // mistake!! = vs. == always
        }

        return false;
    }

    // this is after decimal or integer: as optional part!!
    bool ParseExponent(const string& s, int& i) {
        if (i == static_cast<int>(s.size())) { return false; }
        if (s.at(i) == 'e' || s.at(i) == 'E') {
            i++;  // mistake: forgot this!!
            if (ParseInteger(s, i)) {
                return true;  // i==s.size();  // mistake; return true // here
                              // we expect ending of all
            }
        }

        return false;
    }

   public:
    bool IsNumber(const string& s) {
        int i = 0;
        if (s.size() == 0) return false;

        if (ParseDecimal(s, i)) {
            if (i == static_cast<int>(s.size())) return true;
            if (ParseExponent(s, i)) return i == static_cast<int>(s.size());
        }

        i = 0;
        if (ParseInteger(s, i)) {
            if (i == static_cast<int>(s.size())) return true;
            if (ParseExponent(s, i)) return i == static_cast<int>(s.size());
        }

        return false;
    }

    bool IsNumberV2(const string& s) {
        Tokener tokener(s);
        /*

        S : (+|-) B

        T : (+|-)
        B : numberZ

        Z : eT


         */

        while (true) {
            auto ret = tokener.Next();
        }
        return true;
    }

    class Tokener {
       public:
        Tokener(std::string s) : m_s(std::move(s)) {}
        Tokener(const Tokener&) = default;
        Tokener(Tokener&&) = default;
        Tokener& operator=(const Tokener&) = default;
        Tokener& operator=(Tokener&&) = default;
        virtual ~Tokener() = default;

        enum class token_type {
            PLUS_OR_MINUS,
            NUMBER_SEQUENCE,
            DOT,
            E,
            ERROR,
            END,
        };
        std::pair<token_type, std::string> Next() { return Next(m_cursor); }

        std::pair<token_type, std::string> Seek(int number) {
            int z = m_cursor;
            std::pair<token_type, std::string> ret;
            for (int i = 0; i < number; i++) {
                ret = Next(z);
            }
            return ret;
        }

        bool Consume(int number) {
            int z = m_cursor;
            std::pair<token_type, std::string> ret;
            bool end = false;
            for (int i = 0; i < number; i++) {
                if (end) {
                    return false;  // already end
                }
                ret = Next(z);
                switch (ret.first) {
                    case token_type::ERROR:
                        return false;
                        break;
                    case token_type::END:
                        end = true;
                        break;
                    default:
                        break;
                }
            }
            return true;
        }

        std::pair<token_type, std::string> Next(int& cursor) {
            if (cursor >= static_cast<int>(m_s.size())) {
                return make_pair(token_type::END, " ");
            }
            char const tmp_char = m_s.at(cursor);

            if ('0' <= tmp_char && tmp_char <= '9') {
                std::string tmp = std::to_string(tmp_char);
                cursor++;
                for (size_t i = 0; i < m_s.size(); i++) {
                    if ('0' <= m_s.at(cursor) && m_s.at(cursor) <= '9') {
                        tmp += m_s.at(cursor);
                        cursor++;
                    }
                }
                return make_pair(token_type::NUMBER_SEQUENCE, tmp);
            }
            if ('+' == tmp_char || '-' == tmp_char) {
                char const tmp = tmp_char;
                cursor++;
                return make_pair(token_type::PLUS_OR_MINUS,
                                 std::to_string(tmp));
            }
            if ('e' == tmp_char || 'E' == tmp_char) {
                cursor++;
                return make_pair(token_type::E, std::to_string(tmp_char));
            }
            if ('.' == tmp_char) {
                char const tmp = tmp_char;
                cursor++;
                return make_pair(token_type::DOT, std::to_string(tmp));
            }
            return make_pair(token_type::ERROR, " ");
        }

       private:
        std::string m_s;
        int m_cursor = 0;
    };
};

class Solution2 {
    string m_s;
    string::iterator m_it;

   public:
    bool IsNumber(const std::string& s) {
        m_s = s;
        m_it = m_s.begin();
        return ParseUntrimmedSignedScientificNum();
    }

    // parsing expressions

    bool ParseUntrimmedSignedScientificNum() {
        if (IsEnd()) return false;

        TakeWhileMatches(' ');

        if (!ParseSignedScientificNum()) {
            return false;
        }

        TakeWhileMatches(' ');

        return IsEnd();
    }

    // valid: '1', '1.', '.1', '+.8', '1.1e8', '-1e-10'
    // invalid: '.', ' '
    bool ParseSignedScientificNum() {
        if (IsEnd()) return false;

        if (Match('+') || Match('-')) {
            Take();
        }

        if (!Match('.')) {
            if (!ParseNum()) {
                return false;
            }
            if (TakeIfMatches('.')) {
                ParseNum();
            }
        } else if (TakeIfMatches('.')) {
            if (!ParseNum()) {
                return false;
            }
        }

        if (TakeIfMatches('e') || TakeIfMatches('E')) {
            if (!ParseSignedNum()) {
                return false;
            }
        }

        return true;
    }

    bool ParseSignedNum() {
        if (IsEnd()) return false;

        if (Match('+') || Match('-')) {
            Take();
        }
        return ParseNum();
    }

    bool ParseNum() {
        if (IsEnd()) return false;

        if (!Match('0', '9')) {
            return false;
        }

        TakeWhileMatches('0', '9');
        return true;
    }

    // parser primitives
    void TakeWhileMatches(char c) { while (TakeIfMatches(c)); }

    void TakeWhileMatches(char c, char d) { while (TakeIfMatches(c, d)); }

    bool TakeIfMatches(char c) {
        if (IsEnd()) return false;
        if (Match(c)) {
            Take();
            return true;
        }
        return false;
    }

    bool TakeIfMatches(char c, char d) {
        if (IsEnd()) return false;
        if (Match(c, d)) {
            Take();
            return true;
        }
        return false;
    }

    bool Match(char c) {
        if (IsEnd()) return false;
        return *m_it == c;
    }

    bool Match(char c, char d) {
        if (IsEnd()) return false;
        return *m_it >= c && *m_it <= d;
    }

    char Take() {
        if (IsEnd()) return 10;
        return *m_it++;
    }

    bool IsEnd() { return m_it == m_s.end(); }
};

TEST(validV, t1) {
    std::string const s = "0";
    bool const expected = true;

    Solution sl;
    bool const ret = sl.IsNumber(s);
    EXPECT_EQ(ret, expected);
}

TEST(validnumberV2, t1) {
    std::string const s = "0";
    bool const expected = true;

    Solution2 sl;
    bool const ret = sl.IsNumber(s);
    EXPECT_EQ(ret, expected);
}

TEST(validV, t2) {
    std::string const s = "e";
    bool const expected = false;

    Solution sl;
    bool const ret = sl.IsNumber(s);
    EXPECT_EQ(ret, expected);
}

TEST(validnumberV2, t2) {
    std::string const s = "e";
    bool const expected = false;

    Solution2 sl;
    bool const ret = sl.IsNumber(s);
    EXPECT_EQ(ret, expected);
}

TEST(validV, t4) {
    std::string const s = ".";
    bool const expected = false;

    Solution sl;
    bool const ret = sl.IsNumber(s);
    EXPECT_EQ(ret, expected);
}

TEST(validnumberV2, t4) {
    std::string const s = ".";
    bool const expected = false;

    Solution2 sl;
    bool const ret = sl.IsNumber(s);
    EXPECT_EQ(ret, expected);
}

TEST(validnumberV2, t5) {
    std::vector<std::string> const s = {
        "2",    "0089",  "-0.1", "+3.14", "4.",      "-.9",
        "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"};
    bool const expected = true;

    Solution2 sl;
    for (auto& ptr : s) {
        bool const ret = sl.IsNumber(ptr);
        EXPECT_EQ(ret, expected);
    }
}

TEST(validnumberV2, t6) {
    std::vector<std::string> const s = {"abc",    "1a",  "1e",  "e3",
                                        "99e2.5", "--6", "-+3", "95a54e53"};
    bool const expected = false;

    Solution2 sl;
    for (auto& ptr : s) {
        bool const ret = sl.IsNumber(ptr);
        EXPECT_EQ(ret, expected);
    }
}

}  // namespace
