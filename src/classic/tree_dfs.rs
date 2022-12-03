#[allow(unused)]
struct Tree<T> {
    children: Vec<Tree<T>>,
    value: T,
}

impl<T> Tree<T> {
    #[allow(unused)]
    pub fn new(value: T) -> Self {
        Tree {
            children: vec![],
            value,
        }
    }

    #[allow(unused)]
    pub fn dfs<F: Fn(&T)>(&self, f: F) {
        self.dfs_helper(&f);
    }

    fn dfs_helper<F: Fn(&T)>(&self, f: &F) {
        (f)(&self.value);
        for child in &self.children {
            child.dfs_helper(f);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let t: Tree<i32> = Tree {
            children: vec![
                Tree {
                    children: vec![Tree {
                        children: vec![],
                        value: 14,
                    }],
                    value: 28,
                },
                Tree {
                    children: vec![],
                    value: 80,
                },
            ],
            value: 50,
        };

        t.dfs(|node| {
            println!("{}", node);
        });
    }
}
