extern crate test;

use std::mem::replace;

// bench: find the `BENCH_SIZE` first terms of the fibonacci sequence
#[allow(unused)]
static BENCH_SIZE: usize = 20;

// recursive fibonacci
#[allow(unused)]
fn fibonacci(n: usize) -> u32 {
    if n < 2 {
        1
    } else {
        fibonacci(n - 1) + fibonacci(n - 2)
    }
}

// iterative fibonacci
struct Fibonacci {
    curr: u32,
    next: u32,
}

impl Iterator for Fibonacci {
    type Item = u32;
    #[allow(unused)]
    fn next(&mut self) -> Option<u32> {
        let new_next = self.curr + self.next;
        let new_curr = replace(&mut self.next, new_next);

        Some(replace(&mut self.curr, new_curr))
    }
}

#[allow(unused)]
fn fibonacci_sequence() -> Fibonacci {
    Fibonacci { curr: 1, next: 1 }
}

#[cfg(test)]
mod tests {
    use super::*;
    use test::Bencher;

    // function to benchmark must be annotated with `#[bench]`
    #[bench]
    fn recursive_fibonacci(b: &mut Bencher) {
        // exact code to benchmark must be passed as a closure to the iter
        // method of Bencher
        b.iter(|| (0..BENCH_SIZE).map(fibonacci).collect::<Vec<u32>>());
    }

    #[bench]
    fn iterative_fibonacci(b: &mut Bencher) {
        b.iter(|| fibonacci_sequence().take(BENCH_SIZE).collect::<Vec<u32>>());
    }
}
