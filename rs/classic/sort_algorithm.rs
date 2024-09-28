use std::collections::VecDeque;

#[allow(unused)]
fn bubble_sort<T>(arr: &mut [T])
where
    T: Ord + Copy,
{
    let len = arr.len();
    for i in 0..len {
        for j in 0..len - 1 - i {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
    }
}

#[allow(unused)]
fn quick_sort<T>(arr: &mut [T])
where
    T: Ord + Copy,
{
    fn quick_sort_impl<T: Ord>(arr: &mut [T], low: isize, high: isize) {
        if low < high {
            let p = partition(arr, low, high);
            quick_sort_impl(arr, low, p - 1);
            quick_sort_impl(arr, p + 1, high);
        }
    }

    fn partition<T: Ord>(arr: &mut [T], low: isize, high: isize) -> isize {
        let pivot = high as usize;
        let mut store_index = low - 1;
        let mut last_index = high;

        loop {
            store_index += 1;
            while arr[store_index as usize] < arr[pivot] {
                store_index += 1;
            }
            last_index -= 1;
            while last_index >= 0 && arr[last_index as usize] > arr[pivot] {
                last_index -= 1;
            }
            if store_index >= last_index {
                break;
            }
            arr.swap(store_index as usize, last_index as usize);
        }
        arr.swap(store_index as usize, pivot);
        store_index
    }

    let len = arr.len();
    quick_sort_impl(arr, 0, (len - 1) as isize);
}

#[allow(unused)]
fn merge_sort<T>(seq: &mut [T])
where
    T: Ord + Copy,
{
    let len = seq.len();

    if len <= 1 {
        return;
    }

    merge_sort(&mut seq[0..len / 2]);
    merge_sort(&mut seq[len / 2..]);

    let mut vec = VecDeque::new();
    let mut i = 0;
    let mut left = 0;
    let mut right = len / 2;
    while i < len {
        if left < len / 2 && right < len {
            if seq[left] < seq[right] {
                vec.push_back(seq[left]);
                left += 1;
            } else {
                vec.push_back(seq[right]);
                right += 1;
            }
        } else if left < len / 2 {
            vec.push_back(seq[left]);
            left += 1;
        } else {
            vec.push_back(seq[right]);
            right += 1;
        }
        i += 1;
    }

    i = 0;

    while !vec.is_empty() {
        let v = vec.pop_front().unwrap();
        seq[i] = v;
        i += 1;
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn merge_sort_test() {
        let mut v: Vec<_> = [5, 4, 8, 9, 1].iter().collect();

        let mut v2 = v.clone();

        merge_sort(&mut v);
        v2.sort_unstable();
        assert_eq!(v, v2);
    }

    #[test]
    fn bubble_sort_test() {
        let mut v: Vec<_> = [5, 4, 8, 9, 1].iter().collect();

        let mut v2 = v.clone();

        bubble_sort(&mut v);
        v2.sort_unstable();
        assert_eq!(v, v2);
    }

    #[test]
    fn quick_sort_test() {
        let mut v: Vec<_> = [5, 4, 8, 9, 1].iter().collect();

        quick_sort(&mut v);
        let v2 = v.clone();

        v.sort_unstable();
        assert_eq!(v, v2);
    }
}
