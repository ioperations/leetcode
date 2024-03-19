// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an array of people, people, which are the attributes of some
people in a queue (not necessarily in order). Each people[i] = [hi, ki]
represents the ith person of height hi with exactly ki other people in front who
have a height greater than or equal to hi.

Reconstruct and return the queue that is represented by the input array people.
The returned queue should be formatted as an array queue, where queue[j] = [hj,
kj] is the attributes of the jth person in the queue (queue[0] is the person at
the front of the queue).*/

#include <algorithm>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> ReconstructQueue(vector<vector<int>> &people) {
        if (people.size() < 2) return people;

        vector<vector<int>> ans;
        map<int, vector<int>> heights;

        for (int i = 0; i < (int)people.size(); i++)
            heights[people[i][0]].push_back(people[i][1]);

        for (auto rit = heights.rbegin(); rit != heights.rend(); ++rit) {
            sort(rit->second.begin(), rit->second.end());
            for (int i = 0; i < (int)rit->second.size(); i++)
                ans.insert(ans.begin() + rit->second[i],
                           {rit->first, rit->second[i]});
        }
        return ans;
    }
};

TEST(queue_reconstruction_by_height, t1) {
    std::vector<vector<int>> people{{7, 0}, {4, 4}, {7, 1},
                                    {5, 0}, {6, 1}, {5, 2}};
    std::vector<vector<int>> output = {{5, 0}, {7, 0}, {5, 2},
                                       {6, 1}, {4, 4}, {7, 1}};
    Solution sl;
    auto ert = sl.ReconstructQueue(people);
    /*Explanation:
    Person 0 has height 5 with no other people taller or the same height in
    front. Person 1 has height 7 with no other people taller or the same
    height in front. Person 2 has height 5 with two persons taller or the
    same height in front, which is person 0 and 1. Person 3 has height 6
    with one person taller or the same height in front, which is person 1.
    Person 4 has height 4 with four people taller or the same height in
    front, which are people 0, 1, 2, and 3. Person 5 has height 7 with one
    person taller or the same height in front, which is person 1. Hence
    [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.*/
    EXPECT_EQ(ert, output);
}

TEST(queue_reconstruction_by_height, t2) {
    std::vector<vector<int>> people{{6, 0}, {5, 0}, {4, 0},
                                    {3, 2}, {2, 2}, {1, 4}};
    std::vector<vector<int>> output = {{4, 0}, {5, 0}, {2, 2},
                                       {3, 2}, {1, 4}, {6, 0}};
    Solution sl;
    auto ert = sl.ReconstructQueue(people);
    EXPECT_EQ(ert, output);
}

}  // namespace
