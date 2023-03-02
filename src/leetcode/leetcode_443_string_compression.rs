// Given an array of characters chars, compress it using the following
// algorithm: Begin with an empty string s. For each group of consecutive
// repeating characters in chars: If the group's length is 1, append the
// character to s. Otherwise, append the character followed by the group's
// length. The compressed string s should not be returned separately, but
// instead, be stored in the input character array chars. Note that group
// lengths that are 10 or longer will be split into multiple characters in
// chars. After you are done modifying the input array, return the new length of
// the array.
//
// You must write an algorithm that uses only constant extra space.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn compress(chars: &mut Vec<char>) -> i32 {
        macro_rules! size_dispatch {
            ($number_of_same:ident, $current_size:ident, $current_index:ident, $current_char:ident , $chars:ident) => {
                let vec =
                    ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'];
                if $number_of_same == 1 {
                    $current_size += 1;
                    $chars[$current_index] = $current_char;
                    $current_index += 1;
                } else if $number_of_same < 10 {
                    $current_size += 2;
                    $chars[$current_index] = $current_char;
                    $chars[$current_index + 1] =
                        vec[($number_of_same) as usize];
                    $current_index += 2;
                } else if $number_of_same < 100 {
                    $current_size += (2 + 1);
                    $chars[$current_index] = $current_char;
                    $chars[$current_index + 1] =
                        vec[($number_of_same / 10 % 10) as usize];
                    $chars[$current_index + 2] =
                        vec[($number_of_same % 10) as usize];
                    $current_index += 3;
                } else if $number_of_same < 1000 {
                    $current_size += (2 + 2);
                    $chars[$current_index] = $current_char;
                    $chars[$current_index + 1] =
                        vec[($number_of_same / 100 % 10) as usize];
                    $chars[$current_index + 2] =
                        vec[($number_of_same / 10 % 10) as usize];
                    $chars[$current_index + 3] =
                        vec[($number_of_same % 10) as usize];
                    $current_index += 4;
                } else if $number_of_same < 10000 {
                    $current_size += (2 + 3);
                    $chars[$current_index] = $current_char;
                    $chars[$current_index + 1] =
                        vec[($number_of_same / 1000) as usize];
                    $chars[$current_index + 2] =
                        vec[($number_of_same / 100 % 10) as usize];
                    $chars[$current_index + 3] =
                        vec[($number_of_same / 10 % 10) as usize];
                    $chars[$current_index + 4] =
                        vec[($number_of_same % 10) as usize];
                    $current_index += 5;
                }
            };
        }

        let len = chars.len();
        if len == 0 {
            return 0;
        }
        let mut current_char = chars[0];
        let mut current_size: i32 = 0;
        let mut number_of_same: i32 = 1;
        let mut current_index: usize = 0;

        for i in 1..len {
            if chars[i] == current_char {
                number_of_same += 1;
                continue;
            } else {
                size_dispatch!(
                    number_of_same,
                    current_size,
                    current_index,
                    current_char,
                    chars
                );
                current_char = chars[i];
                number_of_same = 1;
            }
        }

        size_dispatch!(
            number_of_same,
            current_size,
            current_index,
            current_char,
            chars
        );

        current_size
    }
}

#[cfg(test)]
mod test {
    use super::*;

    fn expect_prefix(expects: &[char], results: &[char]) -> bool {
        let len = expects.len();
        let prefix = &results[0..len];
        assert_eq!(*expects, *prefix);
        true
    }

    #[test]
    fn case1_test() {
        let mut chars: Vec<_> = ["a", "a", "b", "b", "c", "c", "c"]
            .into_iter()
            .map(|s| s.as_bytes()[0] as char)
            .collect();
        // Explanation: The groups are "aa", "bb", and "ccc". This compresses to
        // "a2b2c3".
        let output = 6; // and the first 6 characters of the input array should
                        // be: ["a","2","b","2","c","3"]
        let expected: Vec<_> = ["a", "2", "b", "2", "c", "3"]
            .into_iter()
            .map(|s| s.as_bytes()[0] as char)
            .collect();
        let ret = Solution::compress(&mut chars);
        assert_eq!(ret, output);
        expect_prefix(&expected, &chars);
    }

    #[test]
    fn case2_test() {
        let mut chars: Vec<_> =
            ["a"].into_iter().map(|s| s.as_bytes()[0] as char).collect();
        // Explanation:
        // Return 1, and the first character of the input array should be: ["a"]
        // Explanation: The only group is "a", which remains uncompressed since
        // it's a single character.
        let output = 1;
        let expected: Vec<_> =
            ["a"].into_iter().map(|s| s.as_bytes()[0] as char).collect();

        let ret = Solution::compress(&mut chars);
        assert_eq!(ret, output);
        expect_prefix(&expected, &chars);
    }

    #[test]
    fn case3_test() {
        let mut chars: Vec<_> = [
            "a", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b",
        ]
        .into_iter()
        .map(|s| s.as_bytes()[0] as char)
        .collect();

        let expected: Vec<_> = ["a", "b", "1", "2"]
            .into_iter()
            .map(|s| s.as_bytes()[0] as char)
            .collect();
        // Explanation:
        // and the first 4 characters of the input array should be:
        // ["a","b","1","2"]. Explanation: The groups are "a" and
        // "bbbbbbbbbbbb". This compresses to "ab12".
        let output = 4;

        let ret = Solution::compress(&mut chars);
        assert_eq!(ret, output);
        expect_prefix(&expected, &chars);
    }

    #[test]
    fn case4_test() {
        let mut chars: Vec<_> = [
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a",
        ]
        .into_iter()
        .map(|s| s.as_bytes()[0] as char)
        .collect();

        let expected: Vec<_> = ["a", "1", "0", "0"]
            .into_iter()
            .map(|s| s.as_bytes()[0] as char)
            .collect();
        // Explanation:
        // and the first 4 characters of the input array should be:
        // ["a","b","1","2"]. Explanation: The groups are "a" and
        // "bbbbbbbbbbbb". This compresses to "ab12".
        let output = 4;

        let ret = Solution::compress(&mut chars);
        assert_eq!(ret, output);
        expect_prefix(&expected, &chars);
    }

    #[test]
    fn case5_test() {
        let mut chars: Vec<_> = [
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
            "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
        ]
        .into_iter()
        .map(|s| s.as_bytes()[0] as char)
        .collect();

        let expected: Vec<_> = ["a", "1", "0", "0", "0"]
            .into_iter()
            .map(|s| s.as_bytes()[0] as char)
            .collect();
        // Explanation:
        // and the first 4 characters of the input array should be:
        // ["a","b","1","2"]. Explanation: The groups are "a" and
        // "bbbbbbbbbbbb". This compresses to "ab12".
        let output = 5;

        let ret = Solution::compress(&mut chars);
        assert_eq!(ret, output);
        expect_prefix(&expected, &chars);
    }
}
