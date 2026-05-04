#include <array>
#include <cstring>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace {
class QuickSort {
   public:
    void Sort(std::vector<int>& arr, const int start, const int end) {
        if (start >= end) return;

        const int p = Partition(arr, start, end);

        Sort(arr, start, p - 1);

        Sort(arr, p + 1, end);
    }

   private:
    int Partition(std::vector<int>& arr, const int start, const int end) {
        const int pivot = arr.at(start);

        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (arr.at(i) <= pivot) count++;
        }

        const int pivot_index = start + count;
        std::swap(arr.at(pivot_index), arr.at(start));

        int i = start;
        int j = end;

        while (i < pivot_index && j > pivot_index) {
            while (arr.at(i) <= pivot) {
                i++;
            }

            while (arr.at(j) > pivot) {
                j--;
            }

            if (i < pivot_index && j > pivot_index) {
                std::swap(arr.at(i++), arr.at(j--));
            }
        }

        return pivot_index;
    }
};

TEST(algorithmV, t1) {
    std::vector<int> output = {1, 3, 2};

    QuickSort sl;
    sl.Sort(output, 0, 2);
    std::array<int, 3> expected = {1, 2, 3};

    EXPECT_TRUE(0 == memcmp(output.data(), expected.data(), sizeof(expected)));
}
}  // namespace