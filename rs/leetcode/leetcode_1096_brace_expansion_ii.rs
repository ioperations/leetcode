// Under the grammar given below, strings can represent a set of lowercase
// words. Let R(expr) denote the set of words the expression represents.
//
// The grammar can best be understood through simple examples:
//
// Single letters represent a singleton set containing that word.
// R("a") = {"a"}
// R("w") = {"w"}
// When we take a comma-delimited list of two or more expressions, we take the
// union of possibilities. R("{a,b,c}") = {"a","b","c"}
// R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each
// word at most once) When we concatenate two expressions, we take the set of
// possible concatenations between two words where the first word comes from the
// first expression and the second word comes from the second expression.
// R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
// R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg",
// "acdfh", "acefg", "acefh"} Formally, the three rules for our grammar:
//
// For every lowercase letter x, we have R(x) = {x}.
// For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) =
// R(e1) ∪ R(e2) ∪ ... For expressions e1 and e2, we have R(e1 + e2) = {a + b
// for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes
// the cartesian product. Given an expression representing a set of words under
// the given grammar, return the sorted list of words that the expression
// represents.
//
// 1 <= expression.length <= 60
// expression[i] consists of '{', '}', ','or lowercase English letters.
// The given expression represents a set of words based on the grammar given in
// the description.

use std::collections::HashSet;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn brace_expansion_ii(expression: &str) -> Vec<String> {
        let chars: Vec<char> = expression.chars().collect();
        let mut idx = 0usize;
        let set = Self::parse_concat(&chars, &mut idx);
        let mut result: Vec<String> = set.into_iter().collect();
        result.sort();
        result
    }

    // A "concat" is a run of one or more factors, glued together with
    // cartesian-product concatenation. It ends when we hit ',', '}', or EOF.
    fn parse_concat(chars: &[char], idx: &mut usize) -> HashSet<String> {
        let mut result: HashSet<String> = HashSet::new();
        result.insert(String::new());

        while *idx < chars.len() && chars[*idx] != ',' && chars[*idx] != '}' {
            let factor = Self::parse_factor(chars, idx);
            result = Self::cartesian_concat(&result, &factor);
        }

        result
    }

    // A "factor" is either a single letter or a brace-delimited union.
    fn parse_factor(chars: &[char], idx: &mut usize) -> HashSet<String> {
        if chars[*idx] == '{' {
            *idx += 1; // consume '{'
            let set = Self::parse_union(chars, idx);
            *idx += 1; // consume '}'
            set
        } else {
            let mut s = HashSet::new();
            s.insert(chars[*idx].to_string());
            *idx += 1;
            s
        }
    }

    // A "union" is one or more comma-separated "concat"s, unioned together.
    fn parse_union(chars: &[char], idx: &mut usize) -> HashSet<String> {
        let mut result: HashSet<String> = HashSet::new();
        loop {
            let concat = Self::parse_concat(chars, idx);
            result.extend(concat);
            if *idx < chars.len() && chars[*idx] == ',' {
                *idx += 1; // consume ','
            } else {
                break;
            }
        }
        result
    }

    fn cartesian_concat(
        a: &HashSet<String>,
        b: &HashSet<String>,
    ) -> HashSet<String> {
        let mut result = HashSet::with_capacity(a.len() * b.len());
        for x in a {
            for y in b {
                result.insert(format!("{}{}", x, y));
            }
        }
        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let expression = "{a,b}{c,{d,e}}".to_string();
        let output = ["ac", "ad", "ae", "bc", "bd", "be"]
            .iter()
            .map(|v| v.to_string())
            .collect::<Vec<_>>();
        let ret = Solution::brace_expansion_ii(&expression);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let expression = "{{a,z},a{b,c},{ab,z}}".to_string();
        let output = ["a", "ab", "ac", "z"]
            .iter()
            .map(|v| v.to_string())
            .collect::<Vec<_>>();
        let ret = Solution::brace_expansion_ii(&expression);
        assert_eq!(output, ret);
        // Each distinct word is written only once in the final answer.
    }
}
