// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    A string s is called good if there are no two different characters in s that
    have the same frequency.

    Given a string s, return the minimum number of characters you need to delete
   to make s good.

    The frequency of a character in a string is the number of times it appears
   in the string. For example, in the string "aab", the frequency of 'a' is 2,
   while the frequency of 'b' is 1.
*/

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int MinDeletionsV2(string s) {
        if (s.size() == 0) return 0;
        std::map<char, int> map;
        for (auto& ptr : s) {
            map[ptr]++;
        }
        vector<int> vec;

        for (auto& ptr : map) {
            vec.push_back(ptr.second);
        }

        return 0;
    }

    int MinDeletions(string s) {
        /*Approach and Process:

        We are storing all the character frequency of the given string by using
        an unordered map.

        Now we have the frequency of all characters of the given string. So by
        just traversing the unordered map we can easily check which characters'
        frequencies are actually repeating. We have just taken another unordered
        map to check the frequencies are unique or not. ( We can even take a
        vector also for checking this, here we have taken an unordered map for
        better understanding)

        Now if a frequency is not unique (like any other characters' frequency
        in the string is same as current frequency) , then we have to check if
        its any lower frequency spot is available or not i.e. we can delete some
        of that same characters from the string to get any lower frequency spot.
        If we can't find any lower frequency spot then we have to make that
        frequency 0 i.e we have to delete all that particular characters to make
        the frequencies unique.

        Return the count of the total frequency reduction. Simple :)

        Time Complexity - O(N), Space Complexity - O(1)

        */
        unordered_map<int, int> charcnt;
        unordered_map<int, int> uniquefreq;
        int count = 0;

        for (char const i : s) {
            charcnt[i - 'a']++;
        }

        for (auto& it : charcnt) {
            int x = it.second;
            if (uniquefreq[x] != 0) {
                while (x > 0 && uniquefreq[x] != 0) {
                    x--;
                    count++;
                }
            }
            if (x > 0) {
                uniquefreq[x]++;
            }
        }

        return count;
    }
};

TEST(minimum_deletions_to_make_Character_frequencies_unique, t1) {
    string const s = "aab";
    int const out = 0;
    Solution sl;
    int const ret = sl.MinDeletions(s);
    //  s is already good.
    EXPECT_EQ(ret, out);
}

TEST(minimum_deletions_to_make_Character_frequencies_unique, t2) {
    string const s = "aaabbbcc";
    int const out = 2;
    Solution sl;
    int const ret = sl.MinDeletions(s);
    /*You can delete two 'b's resulting in the good string "aaabcc".
    Another way it to delete one 'b' and one 'c' resulting in the good string
    "aaabbc".*/
    EXPECT_EQ(ret, out);
}

TEST(minimum_deletions_to_make_Character_frequencies_unique, t3) {
    string const s = "ceabaacb";
    int const out = 2;
    Solution sl;
    int const ret = sl.MinDeletions(s);
    /*You can delete both 'c's resulting in the good string "eabaab".
    Note that we only care about characters that are still in the string at the
    end (i.e. frequency of 0 is ignored).
    */
    EXPECT_EQ(ret, out);
}

}  // namespace
