// #![feature(generic_associated_types)]
#![feature(type_alias_impl_trait)]
#![feature(generators, generator_trait)]
#![feature(slice_group_by)]
#![feature(test)]
pub mod classic;

mod leetcode {
    automod::dir!("src/leetcode/");
}

pub mod lib {

    use std::fmt::Display;

    #[allow(dead_code)]
    struct Z<'a> {
        part: &'a str,
    }

    impl<'a> Z<'a> {
        #[allow(dead_code)]
        fn annouce_and_return_part<'b>(&'a self, announcement: &'b str) -> &'b str
        where
            'a: 'b,
        {
            println!("Attention please:{announcement}");
            self.part
        }
    }

    /// `add_one` 将指定值加1
    ///
    /// # Example
    /// ```
    /// # let args = 4;
    /// # let ansert = crate::leetcode::lib::add_one(args);
    /// #
    /// # assert_eq!(5,ansert);
    /// ```
    #[must_use]
    #[allow(dead_code)]
    pub fn add_one(x: i32) -> i32 {
        x + 1
    }

    #[allow(dead_code)]
    pub fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
    pub trait Len {
        fn len(self) -> i32;
        fn is_empty(&self) -> bool;
    }

    pub fn longest_t<'a, T>(x: &'a T, y: &'a T) -> &'a T
    where
        T: Len + Copy,
    {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }

    #[allow(dead_code)]
    fn longtest_with_an_announcement<'a, T>(x: &'a str, y: &'a str, ann: T) -> &'a str
    where
        T: Display,
    {
        println!("{ann}");
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
} // Lib
#[cfg(test)]
mod tests {
    use std::fmt::Display;

    use super::*;

    #[test]
    fn logest_test() {
        let hello = String::from("hello");
        {
            let world = String::from("world");
            let ret = lib::longest(hello.as_str(), world.as_str());
            println!("longest is {ret}");
        }
    }

    #[derive(Copy, Clone, Debug)]
    struct TypeZ(i32);

    impl super::lib::Len for TypeZ {
        fn len(self) -> i32 {
            self.0
        }

        fn is_empty(&self) -> bool {
            self.0 == 0
        }
    }
    impl Display for TypeZ {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            f.write_str(format!("TypeZ{{ {} }}", self.0).as_str())
        }
    }
    impl TypeZ {
        fn new(t: i32) -> TypeZ {
            TypeZ(t)
        }
    }

    #[test]
    fn logest_t_test() {
        {
            let i: TypeZ = TypeZ::new(2);
            let j: TypeZ = TypeZ::new(4);
            let ret = lib::longest_t::<TypeZ>(&i, &j);
            println!("longest is {ret}");
        }
    }

    #[test]
    fn main_test() {
        #[allow(unused)]
        #[derive(Debug, PartialEq)]
        enum Detail {
            Empty,
            Unsupported,
            Message(String),
        }
        #[derive(Debug, PartialEq)]
        struct Data {
            a: Detail,
            b: Detail,
        }
        #[allow(unused)]
        #[derive(Debug)]
        struct Item {
            #[allow(unused)]
            name: String,
            data: Vec<Data>,
        }

        #[allow(unused)]
        fn main() {
            let mut lists = vec![
                Item {
                    name: String::from("abc"),
                    data: vec![
                        Data {
                            a: Detail::Empty,
                            b: Detail::Empty,
                        },
                        Data {
                            a: Detail::Unsupported,
                            b: Detail::Empty,
                        },
                        Data {
                            a: Detail::Message(String::from("msg1")),
                            b: Detail::Message(String::from("msg2")),
                        },
                    ],
                },
                Item {
                    name: String::from("def"),
                    data: vec![
                        Data {
                            a: Detail::Empty,
                            b: Detail::Message(String::from("msg3")),
                        },
                        Data {
                            a: Detail::Message(String::from("msg4")),
                            b: Detail::Empty,
                        },
                        Data {
                            a: Detail::Empty,
                            b: Detail::Message(String::from("msg2")),
                        },
                    ],
                },
            ];

            // 比如上例，最终结果如：
            // [
            //      Item {
            //          name: "abc",
            //          data: [
            //                Data {
            //                  a: Message(
            //                        "msg1",
            //                    ),
            //                    b: Message(
            //                        "msg2",
            //                    ),
            //                },
            //            ],
            //      },
            //        Item {
            //            name: "def",
            //            data: [
            //                Data {
            //                    a: Message(
            //                        "msg4",
            //                    ),
            //                    b: Empty,
            //                }
            //            ],
            //        },
            //    ]

            println!("{lists:#?}");

            let z = lists
                .iter_mut()
                .map(|item| {
                    let mut i = 0;
                    while i < item.data.len() {
                        if item.data[i].a == Detail::Empty || item.data[i].a == Detail::Unsupported
                        {
                            item.data.remove(i);
                        } else {
                            i += 1;
                        }
                    }
                })
                .filter(|_| true)
                .collect::<Vec<()>>();
            println!("{z:#?}");
        }
    }
}
