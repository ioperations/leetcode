#[allow(unused)]
pub fn add_binary(a: String, b: String) -> String {
    use std::iter;
    let mut carry = 0;
    let mut cur_sum = 0;
    // 1111
    // 10101
    //  用0填充reverse之后的序列  11110000
    //  用0填充reverse之后的序列  10101000
    //
    let mut char_vec = a
        .as_bytes()
        .iter()
        .rev()
        .chain(iter::repeat(&b'0'))
        .zip(b.as_bytes().iter().rev().chain(iter::repeat(&b'0')))
        .take(a.len().max(b.len()))
        .map(|(ac, bc)| {
            cur_sum = (*ac - b'0') + (*bc - b'0') + carry;
            carry = cur_sum / 2;
            match cur_sum % 2 {
                1 => '1',
                _ => '0',
            }
        })
        .collect::<Vec<_>>();

    if carry == 1 {
        char_vec.push('1');
    }

    char_vec.iter().rev().collect()
}

#[allow(unused)]
fn add_binary_2(a: String, b: String) -> String {
    let mut carry = 0;

    use std::iter;
    let mut z = a
        .as_bytes()
        .iter()
        .rev()
        .chain(iter::repeat(&b'0'))
        .zip(b.as_bytes().iter().chain(iter::repeat(&b'0')))
        .take(a.len().max(b.len()))
        .map(|(a, b)| {
            let this_bit = (*a - b'0') + (*b - b'0') + carry;
            carry = this_bit / 2;
            match this_bit % 2 {
                0 => '0',
                1 => '1',
                _ => '0',
            }
        })
        .collect::<Vec<_>>();

    if carry == 1 {
        z.push('1');
    }

    z.iter().rev().collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn add_binary_1_test() {
        let a: String = String::from("1111");
        let b: String = String::from("10101");
        let ret = add_binary(a, b);
        assert_eq!(ret, "100100");
    }

    #[test]
    fn add_binary_2_test() {
        let a = String::from("11");
        let b = String::from("1");
        let ret = add_binary(a, b);
        assert_eq!(ret, "100");
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;

    #[test]
    fn add_binary_1_test() {
        let a: String = String::from("1111");
        let b: String = String::from("10101");
        let ret = add_binary_2(a, b);
        assert_eq!(ret, "100100");
    }

    #[test]
    fn add_binary_2_test() {
        let a = String::from("11");
        let b = String::from("1");
        let ret = add_binary_2(a, b);
        assert_eq!(ret, "100");
    }
}
