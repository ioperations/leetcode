// Given a string path, which is an absolute path (starting with a slash '/') to
// a file or directory in a Unix-style file system, convert it to the simplified
// canonical path. In a Unix-style file system, a period '.' refers to the
// current directory, a double period '..' refers to the directory up a level,
// and any multiple consecutive slashes (i.e. '//') are treated as a single
// slash '/'. For this problem, any other format of periods such as '...' are
// treated as file/directory names. The canonical path should have the following
// format: The path starts with a single slash '/'.
// Any two directories are separated by a single slash '/'.
// The path does not end with a trailing '/'.
// The path only contains the directories on the path from the root directory to
// the target file or directory (i.e., no period '.' or double period '..')
// Return the simplified canonical path.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn simplify_path(path: &str) -> String {
        let s: Vec<&str> = path.split('/').collect();
        let mut v: Vec<&str> = vec!["/"];

        for i in s {
            if i == ".." {
                if v.len() >= 2 {
                    v.pop();
                    v.pop();
                }
                continue;
            }

            if i == "." {
                continue;
            }

            if !i.is_empty() {
                v.push(i);
                v.push("/");
            }
        }

        if v.len() >= 2 {
            v.pop();
        }

        v.into_iter().collect::<String>()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let path = "/home/";
        let output: String = "/home".into();
        // Explanation: Note that there is no trailing slash after the last
        // directory name.
        let ret = Solution::simplify_path(path);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let path = "/../";
        let output: String = "/".into();
        // Explanation: Note that there is no trailing slash after the last
        // directory name.
        let ret = Solution::simplify_path(path);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let path = "/home//foo/";
        let output: String = "/home/foo".into();
        // Explanation: Note that there is no trailing slash after the last
        // directory name.
        let ret = Solution::simplify_path(path);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let path = "/a/./b/../../c/";
        let output: String = "/c".into();
        // Explanation: Note that there is no trailing slash after the last
        // directory name.
        let ret = Solution::simplify_path(path);
        assert_eq!(ret, output);
    }
}
