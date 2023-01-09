use std::collections::{linked_list, LinkedList};

#[allow(unused)]
fn list_usage() {
    let list = linked_list::LinkedList::from([1, 2, 3, 4]);

    let ret = list.into_iter().map(|x| x * 2).collect::<LinkedList<i32>>();
    println!("{ret:#?}")
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn list_usage_test() {
        list_usage()
    }

    #[test]
    fn list_usage_v2() {
        let list = linked_list::LinkedList::from([1, 2, 3, 4]);
        // let list2 = linked_list::LinkedList::from([10, 12, 14, 16]);

        // let ret = list.into_iter().map(|x| x * 2).chain(list2.into_iter());
        let str = String::from("00000000");
        let ret = list.into_iter().rev().zip(str.as_bytes().iter());
        println!("{:#?}", ret.collect::<LinkedList<(i32, &u8)>>());
    }
}
