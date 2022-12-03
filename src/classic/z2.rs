#[allow(unused)]
fn fb(num: i32) -> i32 {
    match num {
        0 => 0,
        num => num + fb(num - 1),
    }
    /*
    if num == 0{
        1
    }
    else{
        num * fb (num-1)
    }
    */
}

#[allow(unused)]
fn fun2(numthis: u32) -> u32 {
    match numthis {
        0 => 0,
        num => num + fun2(num - 1),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fb_test() {
        assert_eq!(fb(10), 55)
    }

    #[test]
    fn fun2_test() {
        assert_eq!(fun2(10), 55)
    }
}
