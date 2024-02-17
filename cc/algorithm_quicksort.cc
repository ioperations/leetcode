
#include <string.h>
#include <string>
#include <utility>

#include "gtest/gtest.h"

namespace { 
class QuickSort {
    int Partition(int arr[], int start, int end) {
        int pivot = arr[start];

        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] <= pivot) count++;
        }

        // Giving pivot element its correct position
        int pivot_index = start + count;
        std::swap(arr[pivot_index], arr[start]);

        // Sorting left and right parts of the pivot element
        int i = start, j = end;

        while (i < pivot_index && j > pivot_index) {
            while (arr[i] <= pivot) {
                i++;
            }

            while (arr[j] > pivot) {
                j--;
            }

            if (i < pivot_index && j > pivot_index) {
                std::swap(arr[i++], arr[j--]);
            }
        }

        return pivot_index;
    }

   public:
    /**
     * quick sort vec at ragne [begin, end)
     */
    void Sort(int arr[], int start, int end) {
        // base case
        if (start >= end) return;

        // partitioning the array
        int p = Partition(arr, start, end);

        // Sorting the left part
        Sort(arr, start, p - 1);

        // Sorting the right part
        Sort(arr, p + 1, end);
    }
};


TEST(t0, t1) {
    int output[] = {1, 3, 2};

    QuickSort sl;
    sl.Sort(output, 0, 2);
    int expected[] = {1, 2, 3};

    EXPECT_TRUE(0 == memcmp(output, expected, sizeof(expected)));
}

}
