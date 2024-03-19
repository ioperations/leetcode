// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*ou are implementing a program to use as your calendar. We can add a new event
if adding the event will not cause a double booking.

A double booking happens when two events have some non-empty intersection (i.e.,
some moment is common to both events.).

The event can be represented as a pair of integers start and end that represents
a booking on the half-open interval [start, end), the range of real numbers x
such that start <= x < end.

Implement the MyCalendar class:

MyCalendar() Initializes the calendar object.
boolean book(int start, int end) Returns true if the event can be added to the
calendar successfully without causing a double booking. Otherwise, return false
and do not add the event to the calendar.*/
#include <algorithm>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class MyCalendar {
   public:
    MyCalendar() {}

    bool Book(int start, int end) {
        auto slice = make_pair(start, end);
        auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.second <= b.first;
        };
        auto bound = equal_range(slices.begin(), slices.end(), slice, cmp);
        auto it1 = bound.first;
        auto it2 = bound.second;
        if (it1 == it2) {
            slices.insert(it1, slice);
            return true;
        }
        return false;
    }

   private:
    vector<pair<int, int>> slices;
};

TEST(my_calender_i, t1) {
    // Input["MyCalendar", "book", "book", "book"][ [], [ 10, 20 ], [ 15, 25 ],
    // [ 20, 30 ]] Output[null, true, false, true]

    // Explanation
    MyCalendar my_calendar;
    bool ret = my_calendar.Book(10, 20);  // return True
    EXPECT_EQ(ret, true);
    ret =
        my_calendar.Book(15, 25);  // return False, It can not be booked because
    EXPECT_EQ(ret, false);
    // time 15 is already booked by another event.
    ret = my_calendar.Book(
        20, 30);  // return True, The event can be booked, as the first event
    EXPECT_EQ(ret, true);
    // takes every time less than 20, but not including 20.
}

}  // namespace
