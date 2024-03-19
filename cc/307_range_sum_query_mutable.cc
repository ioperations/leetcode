// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums, handle multiple queries of the following types:

Update the value of an element in nums.
Calculate the sum of the elements of nums between indices left and right
inclusive where left <= right. Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array nums.
void update(int index, int val) Updates the value of nums[index] to be val.
int sumRange(int left, int right) Returns the sum of the elements of nums
between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ...
+ nums[right]).
*/
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
class NumArray {
    vector<int> m_arr;
#define ll int
#define vll vector<int>
   public:
    vll vp;  // given array which we are going to use..we will copy it in
             // constructor
    // v is node number tl and tr are node range...node range means
    // range that falls under subtree of node v
    // tl and tr are basically array ranges

    vll segarr;
    ll n;

    ll Combine(ll a, ll b) {
        // you have to combine acc to query type like add,min,max..etc;
        return a + b;
    }

    void Build(ll v, ll tl, ll tr) {
        if (tl == tr) {
            segarr[v] = vp[tl];
            return;
        }

        ll tm = (tl + tr) / 2;
        // building tree in 2 seperate parts
        Build(2 * v, tl, tm);
        Build(2 * v + 1, tm + 1, tr);

        segarr[v] = Combine(segarr[2 * v], segarr[2 * v + 1]);
    }

    void Upd(ll v, ll tl, ll tr, ll ind, ll val) {
        // that update point itself
        if (tl == ind && tr == ind) {
            segarr[v] = val;
            return;
        }

        // we are in wrong region we dont need to update anthing here
        // zero overlap
        if (ind > tr || ind < tl) {
            return;
        }

        ll tm = (tl + tr) / 2;
        // now we will update both regions and after updating them we will
        // combine them

        Upd(2 * v, tl, tm, ind, val);
        Upd(2 * v + 1, tm + 1, tr, ind, val);

        segarr[v] = Combine(segarr[2 * v], segarr[2 * v + 1]);
    }

    void Update(int index, int val) { Upd(1, 0, n - 1, index, val); }
    // here tl and tr are node ranges and l and r are query ranges which will be
    // given to us
    ll Query(ll v, ll l, ll r, ll tl, ll tr) {
        // out of range i.e. invalid case
        if (tl > r || l > tr) {
            return 0;  // for sum its 0...for min it should be inf..i.e. it
                       // should not affect on ans;
        }

        // fully within
        if (l <= tl && r >= tr) {
            return segarr[v];
        }

        // partial overlap
        ll tm = (tl + tr) / 2;

        // perform 2 queries and combine both ans
        ll val1 = Query(2 * v, l, r, tl, tm);
        ll val2 = Query(2 * v + 1, l, r, tm + 1, tr);

        return Combine(val1, val2);
    }

    int SumRange(int left, int right) {
        return Query(1, left, right, 0, n - 1);
    }

    // 0 based indexing segment tree ..value of v always starts from 1
    NumArray(vector<int> &a) {
        n = a.size();
        vp.resize(n);
        vp = a;
        segarr.resize(4 * n);
        Build(1, 0, n - 1);
    }
};

TEST(range_sum_query_mutable, t1) {
    /**
     * Your NumArray object will be instantiated and called as such:
     * NumArray* obj = new NumArray(nums);
     * obj->update(index,val);
     * int param_2 = obj->sumRange(left,right);
     */

    // Input ["NumArray", "sumRange", "update", "sumRange"]
    // [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
    // Output [null, 9, null, 8]

    // Explanation
    vector<int> na{1, 3, 5};
    NumArray num_array(na);
    int ret = num_array.SumRange(0, 2);  // return 1 + 3 + 5 = 9
    EXPECT_EQ(ret, 9);
    num_array.Update(1, 2);          // nums = [1, 2, 5]
    ret = num_array.SumRange(0, 2);  // return 1 + 2 + 5 = 8
    EXPECT_EQ(ret, 8);
}

}  // namespace
