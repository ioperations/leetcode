
/*
 *Design an algorithm that accepts a stream of integers and retrieves the
 product of the last k integers of the stream.
 * Implement the ProductOfNumbers class:
 *
 * ProductOfNumbers() Initializes the object with an empty stream.
 * void add(int num) Appends the integer num to the stream.
 * int getProduct(int k) Returns the product of the last k numbers in the
 current list. You can assume that always the current list has at least k
 numbers.
 * The test cases are generated so that, at any time, the product of any
 contiguous sequence of numbers will fit into a single 32-bit integer without
 overflowing.
 *
 */

#include <vector>
class ProductOfNumbers {
   public:
    ProductOfNumbers() {}
    /*
     * 0 <= num <= 100
      1 <= k <= 4 * 104
      At most 4 * 104 calls will be made to add and getProduct.
      The product of the stream at any point in time will fit in a 32-bit
      integer.
     */

    void add(int num) {
        for (auto &ptr : d) {
            ptr = ptr * num;
        }

        d.push_back(num);
    }

    int getProduct(int k) {
        auto size = d.size();
        return d[size - k];
    }

   private:
    std::vector<int> d;
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

#include <gtest/gtest.h>

TEST(t0, t1) {
    //     ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
    // [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
    //
    // Output
    // [null,null,null,null,null,null,20,40,0,null,32]

    // Explanation
    ProductOfNumbers productOfNumbers;
    productOfNumbers.add(3);  // [3]
    productOfNumbers.add(0);  // [3,0]
    productOfNumbers.add(2);  // [3,0,2]
    productOfNumbers.add(5);  // [3,0,2,5]
    productOfNumbers.add(4);  // [3,0,2,5,4]
    int ret = productOfNumbers.getProduct(2);
    // return 20. The product of the last 2 numbers is 5 * 4 = 20;
    EXPECT_EQ(ret, 20);
    ret = productOfNumbers.getProduct(3);
    // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
    EXPECT_EQ(ret, 40);
    ret = productOfNumbers.getProduct(4);
    // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
    EXPECT_EQ(ret, 0);
    productOfNumbers.add(8);  // [3,0,2,5,4,8]
    ret = productOfNumbers.getProduct(2);
    EXPECT_EQ(ret, 32);
    //  The product of the last 2 numbers is 4 * 8 = 32
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
