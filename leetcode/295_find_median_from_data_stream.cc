/*

The median is the middle value in an ordered integer list. If the size of the
list is even, there is no middle value and the median is the mean of the two
middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data
structure. double findMedian() returns the median of all elements so far.
Answers within 10-5 of the actual answer will be accepted.
*/
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
using namespace std;
class MedianFinder {
   public:
    // Adds a number into the data structure.
    void AddNum(int num) {
        if (min_set.empty() && max_set.empty()) {
            min_set.insert(num);
            return;
        }
        if (min_set.size() < max_set.size()) {
            if (num <= *begin(max_set)) {
                min_set.insert(num);
                return;
            }
            if (num > *begin(max_set)) {
                min_set.insert(*begin(max_set));
                max_set.erase(begin(max_set));
                max_set.insert(num);
                return;
            }
            return;
        }
        if (min_set.size() > max_set.size()) {
            if (num >= *prev(end(min_set))) {
                max_set.insert(num);
                return;
            }
            if (num < *prev(end(min_set))) {
                max_set.insert(*prev(end(min_set)));
                min_set.erase(prev(end(min_set)));
                min_set.insert(num);
                return;
            }
            return;
        }
        if (min_set.size() == max_set.size()) {
            if (num <= *begin(max_set)) {
                min_set.insert(num);
                return;
            }
            if (num > *begin(max_set)) {
                max_set.insert(num);
                return;
            }
            return;
        }
        return;
    }

    // Returns the median of current data stream
    double FindMedian() {
        if (min_set.size() < max_set.size()) {
            return double(*begin(max_set));
        }
        if (min_set.size() > max_set.size()) {
            return double(*prev(end(min_set)));
        }
        if (min_set.size() == max_set.size()) {
            double min_set_max_val = double(*prev(end(min_set)));
            double max_set_min_val = double(*begin(max_set));
            return min_set_max_val / 2.0 + max_set_min_val / 2.0;
        }
        return 0.0;
    }

   private:
    multiset<int> min_set;
    multiset<int> max_set;
};

// BEGIN: Time Limit Exceeded
// class MedianFinder {
// public:

// 	// Adds a number into the data structure.
// 	void addNum(int num) {
// 		rbtree.insert(num);
// 	}

// 	// Returns the median of current data stream
// 	double findMedian() {
// 		if (rbtree.size() & 1) {
// 			return *next(begin(rbtree), rbtree.size() >> 1);
// 		}
// 		double left = double(*next(begin(rbtree), (rbtree.size() >> 1) -
// 1)); 		double right = double(*next(begin(rbtree), rbtree.size()
// >> 1)); 		return left / 2.0 + right / 2.0;
// 	}

// private:
// 	multiset<int> rbtree;
// };
// END: Time Limit Exceeded

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    MedianFinder mf;
    double result = 0.0;
    mf.AddNum(1);
    mf.AddNum(2);

    result = mf.FindMedian();
    EXPECT_NEAR(1.5, result, DBL_EPSILON);

    mf.AddNum(3);

    result = mf.FindMedian();
    EXPECT_NEAR(2.0, result, DBL_EPSILON);

    mf = MedianFinder();

    mf.AddNum(6);
    result = mf.FindMedian();
    EXPECT_NEAR(6.0, result, DBL_EPSILON);

    mf.AddNum(10);
    result = mf.FindMedian();
    EXPECT_NEAR(8.0, result, DBL_EPSILON);

    mf.AddNum(2);
    result = mf.FindMedian();
    EXPECT_NEAR(6.0, result, DBL_EPSILON);

    mf.AddNum(6);
    result = mf.FindMedian();
    EXPECT_NEAR(6.0, result, DBL_EPSILON);

    mf.AddNum(5);
    result = mf.FindMedian();
    EXPECT_NEAR(6.0, result, DBL_EPSILON);

    mf.AddNum(0);
    result = mf.FindMedian();
    EXPECT_NEAR(5.5, result, DBL_EPSILON);

    mf.AddNum(6);
    result = mf.FindMedian();
    EXPECT_NEAR(6.0, result, DBL_EPSILON);

    mf.AddNum(3);
    result = mf.FindMedian();
    EXPECT_NEAR(5.5, result, DBL_EPSILON);

    mf.AddNum(1);
    result = mf.FindMedian();
    EXPECT_NEAR(5.0, result, DBL_EPSILON);

    mf.AddNum(0);
    result = mf.FindMedian();
    EXPECT_NEAR(4.0, result, DBL_EPSILON);

    mf.AddNum(0);
    result = mf.FindMedian();
    EXPECT_NEAR(3.0, result, DBL_EPSILON);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
