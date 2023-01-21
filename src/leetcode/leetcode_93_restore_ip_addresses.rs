// A valid IP address consists of exactly four integers separated by single
// dots. Each integer is between 0 and 255 (inclusive) and cannot have leading
// zeros. For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but
// "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
// Given a string s containing only digits, return all possible valid IP
// addresses that can be formed by inserting dots into s. You are not allowed to
// reorder or remove any digits in s. You may return the valid IP addresses in
// any order.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn restore_ip_addresses(s: &str) -> Vec<String> {
        let mut ret = vec![];
        let mut t = vec![0; 4];
        Self::backtrack(0, &mut ret, &mut t, 0, s);
        ret
    }

    #[allow(unused)]
    fn backtrack(
        i: usize,
        ret: &mut Vec<String>,
        t: &mut Vec<u8>,
        count: usize,
        s: &str,
    ) {
        if i == s.len() {
            if count == 4 {
                ret.push(format!("{}.{}.{}.{}", t[0], t[1], t[2], t[3]));
            }
            return;
        }
        if count >= 4 {
            return;
        }

        if s.as_bytes()[i] == b'0' {
            t[count] = 0;
            Self::backtrack(i + 1, ret, t, count + 1, s);
        } else {
            for j in i..s.len() {
                if let Ok(v) = s[i..=j].parse::<u8>() {
                    t[count] = v;
                    Self::backtrack(j + 1, ret, t, count + 1, s);
                } else {
                    break;
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use hashbrown::HashSet;

    use super::*;

    #[test]
    fn case1_test() {
        let s = "25525511135";
        let output = ["255.255.11.135", "255.255.111.35"];
        let ret = Solution::restore_ip_addresses(s);
        let ret = ret.into_iter().collect::<HashSet<String>>();
        let output = output
            .into_iter()
            .map(|i| i.to_string())
            .collect::<HashSet<String>>();
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let s = "0000";
        let output = ["0.0.0.0"];
        let ret = Solution::restore_ip_addresses(s);
        let ret = ret.into_iter().collect::<HashSet<String>>();
        let output = output
            .into_iter()
            .map(|i| i.to_string())
            .collect::<HashSet<String>>();
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let s = "101023";
        let output = [
            "1.0.10.23",
            "1.0.102.3",
            "10.1.0.23",
            "10.10.2.3",
            "101.0.2.3",
        ];
        let ret = Solution::restore_ip_addresses(s);
        let ret = ret.into_iter().collect::<HashSet<String>>();
        let output = output
            .into_iter()
            .map(|i| i.to_string())
            .collect::<HashSet<String>>();
        assert_eq!(ret, output);
    }
}
