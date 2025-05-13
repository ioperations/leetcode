#[allow(unused)]
struct Solution;

#[allow(unused)]
impl Solution {
    pub fn length_after_transformations(s: &str, t: i32) -> i32 {
        let divided_by = 1_000_000_007;
        let mut counts = [0; 26];
        for &c in s.as_bytes() {
            counts[(c - b'a') as usize] += 1;
        }
        let mut i = 0;
        for _ in 0..t {
            let j = i;
            i = (i + 25) % 26;
            counts[j] = (counts[j] + counts[i]) % divided_by;
        }
        let mut ans = 0;
        for cnt in counts {
            ans = (ans + cnt) % divided_by;
        }
        ans
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_case1() {
        let s = "abc";
        let t = 3;
        let result = Solution::length_after_transformations(s, t);
        assert_eq!(result, 3);
    }

    #[test]
    fn test_case2() {
        let s = "a";
        let t = 1;
        let result = Solution::length_after_transformations(s, t);
        assert_eq!(result, 1);
    }
}
