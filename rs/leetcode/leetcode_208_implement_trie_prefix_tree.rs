// A trie (pronounced as "try") or prefix tree is a tree data structure used to
// efficiently store and retrieve keys in a dataset of strings. There are
// various applications of this data structure, such as autocomplete and
// spellchecker. Implement the Trie class:
// Trie() Initializes the trie object.
// void insert(String word) Inserts the string word into the trie.
// boolean search(String word) Returns true if the string word is in the trie
// (i.e., was inserted before), and false otherwise. boolean startsWith(String
// prefix) Returns true if there is a previously inserted string word that has
// the prefix prefix, and false otherwise.

use std::boxed::Box;

#[allow(unused)]
#[derive(Debug)]
struct TrieNode {
    c_byte: u8,
    is_word: bool,
    children: [Option<Box<TrieNode>>; 26],
}

impl TrieNode {
    #[allow(unused)]
    fn new(c_byte: u8) -> Self {
        TrieNode {
            c_byte,
            is_word: false,
            children: Default::default(),
        }
    }
}

#[derive(Debug)]
struct Trie {
    #[allow(unused)]
    head: TrieNode,
}

impl Trie {
    #[allow(unused)]
    fn new() -> Self {
        Trie {
            head: TrieNode::new(b'\0'),
        }
    }

    /// Inserts a word into the trie.
    #[allow(unused)]
    fn insert(&mut self, word: &str) {
        let mut curr: &mut TrieNode = &mut self.head;
        for b in word.bytes() {
            let e_byte = Self::e_byte(b);
            let node = TrieNode::new(e_byte);
            curr = curr.children[e_byte as usize].get_or_insert(Box::new(node));
        }
        curr.is_word = true;
    }

    /// Returns if the word is in the trie.
    #[allow(unused)]
    fn search(&self, word: &str) -> bool {
        match self.search_node(word) {
            Some(node) => node.is_word,
            None => false,
        }
    }

    /// Returns if there is any word in the trie that starts with the given
    /// prefix.
    #[allow(unused)]
    fn starts_with(&self, prefix: &str) -> bool {
        self.search_node(prefix).is_some()
    }

    #[allow(unused)]
    fn search_node(&self, prefix: &str) -> Option<&TrieNode> {
        let mut curr: &TrieNode = &self.head;
        for b in prefix.bytes() {
            let e_byte = Self::e_byte(b);
            match &curr.children[e_byte as usize] {
                Some(node) => curr = node,
                None => return None,
            }
        }

        Some(curr)
    }

    #[allow(unused)]
    fn e_byte(b: u8) -> u8 {
        b - b'a'
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        //  Input
        // ["Trie", "insert", "search", "search", "startsWith", "insert",
        // "search"] [[], ["apple"], ["apple"], ["app"], ["app"],
        // ["app"], ["app"]]
        // Output [null, null, true, false, true,
        // null, true] Explanation
        let mut trie = Trie::new();
        trie.insert("apple");
        let ret = trie.search("apple"); // return True
        assert!(ret);
        let ret = trie.search("app"); // return False
        assert!(!ret);
        let ret = trie.starts_with("app"); // return True
        assert!(ret);
        trie.insert("app");
        let ret = trie.search("app"); // return True
        assert!(ret);
    }
}
