package leetcode;

import std.unittest.*;

@Test
class AddTest {
    @TestCase
    func testAdd() {
        expectEqual<Int16>("hello", "world", add(1, 2), 3);
    }
}
