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
        while (j < (int)s.size() && isdigit(s[j])) j++;
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
        if (i == (int)s.size()) return false;

        // optionally + or -
        if (s[i] == '+' || s[i] == '-') i++;

        if (i == (int)s.size())  // end already?
            return false;        // TODO: when false, undo side effect??

        if (ParseDigits(s, i)) {
            if (i == (int)s.size()) return false;
            if (s[i] == '.') {
                i++;
                //  if (i==s.size())  // how to handle 46.e3 ??  conflicting
                //  semantics
                //     return true;
                if (ParseDigits(s, i))
                    return true;  // mistake:  return i==s.size(); // it can
                                  // follow more things
                return true;      // still true , most tricky part here !!!
            }
        } else if (s[i] == '.') {
            i++;
            if (ParseDigits(s, i)) return true;  // mistake return i==s.size();
        }

        return false;
    }

    // integer may be a part of the component, followed by more things
    bool ParseInteger(const string& s, int& i) {
        if (i == (int)s.size()) return false;
        // optionally + or -
        if (s[i] == '+' || s[i] == '-') i++;

        if (ParseDigits(s, i))
            return true;  // return i==s.size(); // mistake!! = vs. == always

        return false;
    }

    // this is after decimal or integer: as optional part!!
    bool ParseExponent(const string& s, int& i) {
        if (i == (int)s.size()) return false;
        if (s[i] == 'e' || s[i] == 'E') {
            i++;  // mistake: forgot this!!
            if (ParseInteger(s, i))
                return true;  // i==s.size();  // mistake; return true // here
                              // we expect ending of all
        }

        return false;
    }

   public:
    bool IsNumber(string s) {
        int i = 0;
        if (s.size() == 0) return false;

        if (ParseDecimal(s, i)) {
            if (i == (int)s.size()) return true;
            if (ParseExponent(s, i)) return i == (int)s.size();
        }

        i = 0;
        if (ParseInteger(s, i)) {
            if (i == (int)s.size()) return true;
            if (ParseExponent(s, i)) return i == (int)s.size();
        }

        return false;
    }

    bool IsNumberV2(string s) {
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
        Tokener(std::string s) : m_s(std::move(s)) {};
        virtual ~Tokener() = default;

        enum token_type {
            PLUS_OR_MINUS,
            NUMBER_SEQUENCE,
            DOT,
            E,
            ERROR,
            END,
        };
        std::pair<token_type, std::string> Next() { return Next(cursor); }

        std::pair<token_type, std::string> Seek(int number) {
            int z = cursor;
            std::pair<token_type, std::string> ret;
            for (int i = 0; i < number; i++) {
                ret = Next(z);
            }
            return ret;
        }

        bool Consume(int number) {
            int z = cursor;
            std::pair<token_type, std::string> ret;
            bool end = false;
            for (int i = 0; i < number; i++) {
                if (end) {
                    return false;  // already end
                }
                ret = Next(z);
                switch (ret.first) {
                    case ERROR:
                        return false;
                        break;
                    case END:
                        end = true;
                        break;
                    default:
                        break;
                }
            }
            return true;
        }

        std::pair<token_type, std::string> Next(int& cursor) {
          if (cursor >= (int)m_s.size()) {
            return make_pair(token_type::END, " ");
          }
          char const tmp_char = m_s[cursor];

          if ('0' <= tmp_char && tmp_char <= '9') {
            std::string tmp = std::to_string(tmp_char);
            cursor++;
            for (size_t i = 0; i < m_s.size(); i++) {
              if ('0' <= m_s[cursor] && m_s[cursor] <= '9') {
                tmp += m_s[cursor];
                cursor++;
              }
            }
            return make_pair(token_type::NUMBER_SEQUENCE, tmp);
            }
            if ('+' == tmp_char || '-' == tmp_char) {
              char const tmp = tmp_char;
              cursor++;
              return make_pair(token_type::PLUS_OR_MINUS, std::to_string(tmp));
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
        int cursor = 0;
    };
};

class Solution2 {
    string m_s;
    string::iterator m_it;

   public:
    bool IsNumber(string s) {
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

TEST(valid_number, t1) {
  std::string const s = "0";
  bool const expected = true;

  Solution sl;
  bool const ret = sl.IsNumber(s);
  EXPECT_EQ(ret, expected);
}

TEST(valid_number_v2, t1) {
  std::string const s = "0";
  bool const expected = true;

  Solution2 sl;
  bool const ret = sl.IsNumber(s);
  EXPECT_EQ(ret, expected);
}

TEST(valid_number, t2) {
  std::string const s = "e";
  bool const expected = false;

  Solution sl;
  bool const ret = sl.IsNumber(s);
  EXPECT_EQ(ret, expected);
}

TEST(valid_number_v2, t2) {
  std::string const s = "e";
  bool const expected = false;

  Solution2 sl;
  bool const ret = sl.IsNumber(s);
  EXPECT_EQ(ret, expected);
}

TEST(valid_number, t4) {
  std::string const s = ".";
  bool const expected = false;

  Solution sl;
  bool const ret = sl.IsNumber(s);
  EXPECT_EQ(ret, expected);
}

TEST(valid_number_v2, t4) {
  std::string const s = ".";
  bool const expected = false;

  Solution2 sl;
  bool const ret = sl.IsNumber(s);
  EXPECT_EQ(ret, expected);
}

TEST(valid_number_v2, t5) {
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

TEST(valid_number_v2, t6) {
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
