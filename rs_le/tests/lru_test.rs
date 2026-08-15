use rs_le::lru_cache;

use std::thread;
use std::time::Duration;

// Cache up to 10 unique argument pairs
#[lru_cache(10)]
fn expensive_calculation(x: u32, y: u32) -> u32 {
    println!("Calculating values for ({}, {})... (Cache Miss)", x, y);
    thread::sleep(Duration::from_millis(500)); // Simulate hard workload
    x + y
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case_test() {
        // First invocation: Cache miss (takes 500ms)
        println!("Result 1: {}", expensive_calculation(10, 20));

        // Second invocation: Cache hit (instantaneous return)
        println!("Result 2: {}", expensive_calculation(10, 20));

        // Different arguments: Cache miss (takes 500ms)
        println!("Result 3: {}", expensive_calculation(5, 5));
    }
}
