package leetcode;

import std.unittest.*;

@Test
class AddTest {
    @TestCase
    func testAdd() {
        expectEqual<Int32>("hello", "world", add(1, 2), 3);
    }

    @TestCase
    func testAddNegativeNumbers() {
        expectEqual<Int32>("negative numbers", "add(-1, -2)", add(-1, -2), -3);
    }

    @TestCase
    func testAddZero() {
        expectEqual<Int32>("zero", "add(0, 0)", add(0, 0), 0);
    }

    @TestCase
    func testAddLargeNumbers() {
        expectEqual<Int32>("large numbers", "add(30000, 10000)", add(30000, 10000), 40000);
    }
}
