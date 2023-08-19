// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <gtest/gtest.h>
#include <limits.h>
#include <time.h>

#include <iostream>
#include <vector>

using namespace std;

/// 寻找两个已经排好序的数组的中位数
/// 要求算法时间复杂度是O(log(m+n))
namespace { 
class Solution {
   public:
    double FindMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        clock_t start, end;

        start = clock();
        double tmp = ImplV1(nums1, nums2);
        end = clock();
        std::cout << "v1 const time " << end - start << std::endl;

        start = clock();
        tmp = ImplV2(nums1, nums2);
        end = clock();
        std::cout << "v2 const time " << end - start << std::endl;

        start = clock();
        tmp = ImplV3(nums1, nums2);
        end = clock();
        std::cout << "v3 const time " << end - start << std::endl;
        return tmp;
    }

   private:
    /// 至少可以做到O(m+n)
    double ImplV1(vector<int> &nums1, vector<int> &nums2) {
        vector<int> merged;
        size_t i = 0, j = 0;
        merged.resize(nums1.size() + nums2.size());
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                merged.push_back(nums1[i]);
                i++;
            } else {
                merged.push_back(nums2[j]);
                j++;
            }
        }
        while (i < nums1.size()) {
            merged.push_back(nums1[i]);
            i++;
        }
        while (j < nums2.size()) {
            merged.push_back(nums2[j]);
            j++;
        }
        auto middle = merged.size() / 2;
        if (merged.size() % 2 == 0) {
            auto a = merged[middle - 1];
            auto b = merged[middle];

            return (a + b) / 2.;
        }
        return merged[middle];
    }

    double ImplV2(vector<int> &nums1, vector<int> &nums2) {
        if (nums1.size() > nums2.size()) {
            return FindMedianSortedArrays(nums2, nums1);
        }
        int x = nums1.size();
        int y = nums2.size();

        int high = x;
        int low = 0;
        while (low <= high) {
            int divide_x = low + (high - low) / 2;
            int divide_y = (x + y + 1) / 2 - divide_x;

            double max_left_x = (divide_x == 0 ? INT_MIN : nums1[divide_x - 1]);
            double min_right_x = (divide_x == x ? INT_MAX : nums1[divide_x]);

            double max_left_y = (divide_y == 0 ? INT_MIN : nums2[divide_y - 1]);
            double min_right_y = (divide_y == y ? INT_MAX : nums2[divide_y]);

            if (max_left_x <= min_right_y && max_left_y <= min_right_x) {
                if ((x + y) % 2 == 0) {
                    return (max(max_left_x, max_left_y) +
                            min(min_right_x, min_right_y)) /
                           2.0;
                }
                return max(max_left_x, max_left_y);
            }
            if (max_left_x > min_right_y) {
                high = divide_x - 1;
            } else {
                low = divide_x + 1;
            }
        }
        return 0;
    }

    double ImplV3(vector<int> &nums1, vector<int> &nums2) {
        int m = nums1.size(), n = nums2.size();

        if (!m)
            return n & 1 ? nums2[n / 2]
                         : (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0;
        if (!n)
            return m & 1 ? nums1[m / 2]
                         : (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0;

        if ((m + n) & 1)
            return Median(nums1, nums2, 0, m - 1, 0, n - 1, (m + n) / 2);

        return (Median(nums1, nums2, 0, m - 1, 0, n - 1, (m + n) / 2 - 1) +
                Median(nums1, nums2, 0, m - 1, 0, n - 1, (m + n) / 2)) /
               2.0;
    }

    double Median(vector<int> &a, vector<int> &b, int s1, int e1, int s2,
                  int e2, int tar) {
        int la, lb, ma, mb, m = max(e1 - s1 + 1, 0), n = max(e2 - s2 + 1, 0),
                            ans;
        if (!m) return b[s2 + tar];
        if (!n) return a[s1 + tar];

        la = m / 2;
        lb = n / 2;
        ma = a[s1 + la];
        mb = b[s2 + lb];

        if (la + lb >= tar) {
            if (ma > mb)
                ans = Median(a, b, s1, s1 + la - 1, s2, e2, tar);
            else
                ans = Median(a, b, s1, e1, s2, s2 + lb - 1, tar);
        } else {
            if (ma > mb)
                ans = Median(a, b, s1, e1, s2 + lb + 1, e2, tar - lb - 1);
            else
                ans = Median(a, b, s1 + la + 1, e1, s2, e2, tar - la - 1);
        }
        return ans;
    }
};
} 

namespace { 
TEST(t1, t2) {
    Solution n;

    vector<int> n1{1, 2, 3, 4, 5};
    vector<int> n2{1, 2, 3, 4, 5};

    vector<int> n3{};
    vector<int> n4{1};

    EXPECT_EQ(3.0, n.FindMedianSortedArrays(n1, n2));
    EXPECT_EQ(3.0, n.FindMedianSortedArrays(n1, n3));
    EXPECT_EQ(1.0, n.FindMedianSortedArrays(n3, n4));
}

}
