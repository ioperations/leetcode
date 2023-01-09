mod summary {
    pub trait Summary {
        fn summary(&self) -> String;
    }

    #[allow(dead_code)]
    enum Sex {
        Male,
        Female,
        Other(String),
    }

    struct Post {
        email: String,
        name: String,
        id: i32,
        sex: Sex,
    }

    struct Weibo {
        name: String,
        id: i32,
        sex: Sex,
    }

    impl Summary for Post {
        fn summary(&self) -> String {
            match &self.sex {
                Sex::Male => {
                    format!(
                        "my name is {}, email is {}, my id id {}, my sex is MALE",
                        self.name, self.email, self.id
                    )
                }
                Sex::Female => {
                    format!(
                        "my name is {}, email is {}, my id id {}, my sex is FAMALE",
                        self.name, self.email, self.id
                    )
                }
                Sex::Other(_) => {
                    format!(
                        "my name is {}, email is {}, my id id {}, my sex is private",
                        self.name, self.email, self.id
                    )
                }
            }
        }
    }

    impl Summary for Weibo {
        fn summary(&self) -> String {
            match &self.sex {
                Sex::Male => {
                    format!(
                        "my name is {}, my id id {}, my sex is MALE",
                        self.name, self.id
                    )
                }
                Sex::Female => {
                    format!(
                        "my name is {}, my id id {}, my sex is FAMALE",
                        self.name, self.id
                    )
                }
                Sex::Other(_) => {
                    format!(
                        "my name is {}, my id id {}, my sex is private",
                        self.name, self.id
                    )
                }
            }
        }
    }

    #[allow(dead_code)]
    pub fn returns_summarizable(switch: bool) -> Box<dyn Summary> {
        if switch {
            Box::new(Post {
                email: String::from("unknown@unknown.com"),
                name: String::from("undefined"),
                id: 0,
                sex: Sex::Other(String::from("private")),
            })
        } else {
            Box::new(Weibo {
                id: 0,
                name: String::from("undefined"),
                sex: Sex::Other(String::from("private")),
            })
        }
    }

    #[allow(dead_code)]
    pub fn return_impl_trait(_: bool) -> impl Summary {
        Post {
            email: String::from("unknown@unknown.com"),
            name: String::from("undefined"),
            id: 0,
            sex: Sex::Other(String::from("private")),
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::classic::dyn_t::summary::Summary;

    use super::*;

    #[test]
    fn returns_summarizable_test() {
        let string = summary::returns_summarizable(true).summary();
        println!("{string}")
    }

    #[test]
    fn returns_summarizable2_test() {
        let string = summary::returns_summarizable(false).summary();
        println!("{string}")
    }

    #[test]
    fn reutrn_impl_test() {
        /*
         * impl trait 和dyn trait都是高级特性 `鸭子模型`的实现
         * impl trait 是静态的，在编译期间就可以确定的
         * dyn trait 是动态的，在运行期间才能确定的
         */
        let post = summary::return_impl_trait(true).summary();
        println!("{post}");
    }
}
