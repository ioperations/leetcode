// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
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
#include <cfloat>
#include <iterator>
#include <set>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class MedianFinder {
   public:
    // Adds a number into the data structure.
    void AddNum(int num) {
        if (m_min_set.empty() && m_max_set.empty()) {
            m_min_set.insert(num);
            return;
        }
        if (m_min_set.size() < m_max_set.size()) {
            if (num <= *begin(m_max_set)) {
                m_min_set.insert(num);
                return;
            }
            if (num > *begin(m_max_set)) {
                m_min_set.insert(*begin(m_max_set));
                m_max_set.erase(begin(m_max_set));
                m_max_set.insert(num);
                return;
            }
            return;
        }
        if (m_min_set.size() > m_max_set.size()) {
            if (num >= *prev(end(m_min_set))) {
                m_max_set.insert(num);
                return;
            }
            if (num < *prev(end(m_min_set))) {
                m_max_set.insert(*prev(end(m_min_set)));
                m_min_set.erase(prev(end(m_min_set)));
                m_min_set.insert(num);
                return;
            }
            return;
        }
        if (m_min_set.size() == m_max_set.size()) {
            if (num <= *begin(m_max_set)) {
                m_min_set.insert(num);
                return;
            }
            if (num > *begin(m_max_set)) {
                m_max_set.insert(num);
                return;
            }
            return;
        }
        return;
    }

    // Returns the median of current data stream
    double FindMedian() {
        if (m_min_set.size() < m_max_set.size()) {
            return double(*begin(m_max_set));
        }
        if (m_min_set.size() > m_max_set.size()) {
            return double(*prev(end(m_min_set)));
        }
        if (m_min_set.size() == m_max_set.size()) {
            double const min_set_max_val = double(*prev(end(m_min_set)));
            double const max_set_min_val = double(*begin(m_max_set));
            return min_set_max_val / 2.0 + max_set_min_val / 2.0;
        }
        return 0.0;
    }

   private:
    multiset<int> m_min_set;
    multiset<int> m_max_set;
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

TEST(find_median_from_data_stream, t1) {
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

}  // namespace
