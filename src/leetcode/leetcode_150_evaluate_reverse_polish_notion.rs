// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
// Valid operators are +, -, *, and /. Each operand may be an integer or another
// expression. Note that division between two integers should truncate toward
// zero. It is guaranteed that the given RPN expression is always valid.
// That means the expression would always evaluate to a result,
// and there will not be any division by zero operation.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn eval_rpn(tokens: &[String]) -> i32 {
        let mut stack = Vec::with_capacity(tokens.len());

        for i in tokens {
            match i.as_str() {
                "+" => {
                    let second = stack.pop().unwrap();
                    let first = stack.pop().unwrap();
                    stack.push(first + second);
                }
                "-" => {
                    let second = stack.pop().unwrap();
                    let first = stack.pop().unwrap();
                    stack.push(first - second);
                }
                "*" => {
                    let second = stack.pop().unwrap();
                    let first = stack.pop().unwrap();
                    stack.push(first * second);
                }
                "/" => {
                    let second = stack.pop().unwrap();
                    let first = stack.pop().unwrap();
                    stack.push(first / second);
                }
                v => {
                    stack.push(v.parse::<i32>().unwrap());
                }
            }
        }
        stack.pop().unwrap()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let tokens = ["2", "1", "+", "3", "*"].map(String::from);
        let output = 9;
        // Explanation: ((2 + 1) * 3) = 9
        let ret = Solution::eval_rpn(&tokens);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let tokens = ["4", "13", "5", "/", "+"].map(String::from);
        let output = 6;
        // (4 + (13 / 5)) = 6
        let ret = Solution::eval_rpn(&tokens);
        assert_eq!(output, ret);
    }

    #[test]
    fn case3_test() {
        let tokens = [
            "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+",
        ]
        .map(String::from);

        let output = 22;
        // ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
        // = ((10 * (6 / (12 * -11))) + 17) + 5
        // = ((10 * (6 / -132)) + 17) + 5
        // = ((10 * 0) + 17) + 5
        // = (0 + 17) + 5
        // = 17 + 5
        // = 22
        let ret = Solution::eval_rpn(&tokens);
        assert_eq!(output, ret);
    }
}
