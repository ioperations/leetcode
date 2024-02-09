// implement the generic function below
// implement `fn summary` to make the code work
// fix the errors without removing any code line
trait Summary {
    #[allow(unused)]
    fn summarize(&self) -> String;
}

#[derive(Debug)]
#[allow(unused)]
struct Post {
    title: String,
    author: String,
    content: String,
}

impl Summary for Post {
    #[allow(unused)]
    fn summarize(&self) -> String {
        format!("The author of post {} is {}", self.title, self.author)
    }
}

#[derive(Debug)]
struct Weibo {
    username: String,
    content: String,
}

impl Summary for Weibo {
    fn summarize(&self) -> String {
        format!("{} published a weibo {}", self.username, self.content)
    }
}
#[cfg(test)]
mod tests {
    use super::*;

    // implement `fn summary` below
    fn summary(a: &dyn Summary) -> String {
        a.summarize()
    }

    #[test]
    fn func1_test() {
        let post = Post {
            title: "Popular Rust".to_string(),
            author: "Sunface".to_string(),
            content: "Rust is awesome!".to_string(),
        };
        let weibo = Weibo {
            username: "sunface".to_string(),
            content: "Weibo seems to be worse than Tweet".to_string(),
        };

        summary(&post);
        summary(&weibo);

        println!("{post:?}");
        println!("{weibo:?}");
    }
}
