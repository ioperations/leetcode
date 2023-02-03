// Given an m x n grid of characters board and a string word, return true if
// word exists in the grid.
//
// The word can be constructed from letters of sequentially adjacent cells,
// where adjacent cells are horizontally or vertically neighboring. The same
// letter cell may not be used more than once.

#[allow(unused)]
struct Solution;

#[allow(unused)]
struct Context {
    s: Vec<char>,
    row: i32,
    col: i32,
    index: i32,
    dir: Vec<i32>,
    decision: bool,
}

use tracing::debug;

impl Solution {
    #[allow(unused)]
    #[tracing::instrument(level = "debug", skip_all)]
    pub fn exist(board: Vec<Vec<char>>, word: &str) -> bool {
        assert!(!board.is_empty());
        let mut board = board;
        let row = board.len();
        let column = board[0].len();
        let word = word.chars().collect::<Vec<char>>();
        let mut context = Context {
            s: vec![],
            row: row as i32,
            col: column as i32,
            index: 0,
            dir: vec![1, 0, -1, 0, 1],
            decision: false,
        };

        debug!("entering backtrack row:{row}, column:{column}");

        for i in 0..row {
            for j in 0..column {
                if board[i][j] == word[0] {
                    Self::back_track(&mut context, i, j, &mut board, &word);
                }
            }
        }
        context.decision
    }

    #[allow(unused)]
    fn back_track(
        context: &mut Context,
        i: usize,
        j: usize,
        board: &mut Vec<Vec<char>>,
        word: &Vec<char>,
    ) {
        if context.index >= word.len() as i32 {
            return;
        }
        if word[context.index as usize] != board[i][j] {
            return;
        }

        context.s.push(board[i][j]);
        board[i][j] = '?';
        context.index += 1;

        if context.s == *word {
            context.decision = true; // record solotion
        }

        for k in 0..=3 {
            if Self::is_safe(
                context,
                i as i32 + context.dir[k],
                j as i32 + context.dir[k + 1],
            ) {
                Self::back_track(
                    context,
                    (i as i32 + context.dir[k]) as usize,
                    (j as i32 + context.dir[k + 1]) as usize,
                    board,
                    word,
                );
            }
        }

        board[i][j] = context.s[context.s.len() - 1];
        context.s.pop();
        context.index -= 1;
    }

    #[allow(unused)]
    fn is_safe(contet: &Context, i: i32, j: i32) -> bool {
        (i >= 0 && j >= 0 && i < contet.row && j < contet.col)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        // ___ ___ ___ ___
        // | A | B | C | E |
        // |_-_|_-_|_-_|___|
        // | S | F | C | S |
        // |___|___|_-_|___|
        // | A | D | E | E |
        // |___|_-_|_-_|___|
        let v = vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ];
        let word = String::from("ABCCED");
        let ret = Solution::exist(v, word.as_str());
        assert!(ret);
    }

    #[test]
    fn case2_test() {
        // ___ ___ ___ ___
        // | A | B | C | E |
        // |___|___|___|___|
        // | S | F | C | S |
        // |___|___|___|_-_|
        // | A | F | D | E |
        // |___|___|_-_|_-_|
        let v = vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ];
        let word = String::from("SEE");
        let ret = Solution::exist(v, word.as_str());
        assert!(ret);
    }

    #[test]
    fn case3_test() {
        // ___ ___ ___ ___
        // | A | B | C | E |
        // |___|___|___|___|
        // | S | F | C | S |
        // |___|___|___|___|
        // | A | F | D | E |
        // |___|___|___|___|

        let v = vec![
            vec!['A', 'B', 'C', 'E'],
            vec!['S', 'F', 'C', 'S'],
            vec!['A', 'D', 'E', 'E'],
        ];
        let word = String::from("ABCB");
        let ret = Solution::exist(v, word.as_str());
        assert!(!ret);
    }

    #[test]
    fn case4_test() {
        // ___ ___ ___ ___
        // | A | B | C | E |
        // |___|___|___|___|
        // | S | F | C | S |
        // |___|___|___|___|
        // | A | F | D | E |
        // |___|___|___|___|

        let v = vec![
            vec!['A', 'A', 'A', 'A', 'A', 'A'],
            vec!['A', 'A', 'A', 'A', 'A', 'A'],
            vec!['A', 'A', 'A', 'A', 'A', 'A'],
            vec!['A', 'A', 'A', 'A', 'A', 'A'],
            vec!['A', 'A', 'A', 'A', 'A', 'A'],
            vec!['A', 'A', 'A', 'A', 'A', 'A'],
        ];
        let word = String::from("AAAAAAAAAAAAAAB");
        let ret = Solution::exist(v, word.as_str());
        assert!(!ret);
    }
}
