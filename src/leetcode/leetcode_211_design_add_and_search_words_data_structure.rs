// Design a data structure that supports adding new words and finding if a
// string matches any previously added string.↳
//
// Implement the WordDictionary class:
// WordDictionary() Initializes the object.
// void addWord(word) Adds word to the data structure, it can be matched later.
// bool search(word) Returns true if there is any string in the data structure
// that matches word or false otherwise. word may contain dots '.' where dots
// can be matched with any letter.

#[allow(unused)]
struct TrieNode {
    c_byte: u8,
    is_end: bool,
    next: [Option<Box<TrieNode>>; 26],
}

impl TrieNode {
    #[allow(unused)]
    fn new(c_byte: u8) -> Self {
        TrieNode {
            c_byte,
            is_end: false,
            next: Default::default(),
        }
    }
}

#[allow(unused)]
struct WordDictionary {
    // 1 <= word.length <= 25
    // word in addWord consists of lowercase English letters.
    // word in search consist of '.' or lowercase English letters.
    // There will be at most 3 dots in word for search queries.
    // At most 104 calls will be made to addWord and search.
    root: Box<TrieNode>,
}

/// `&self` means the method takes an immutable reference.
/// If you need a mutable reference, change it to `&mut self` instead.
impl WordDictionary {
    #[allow(unused)]
    fn new() -> Self {
        WordDictionary {
            root: Box::new(TrieNode::new(b'\0')),
        }
    }

    #[allow(unused)]
    fn add_word(&mut self, word: &str) {
        let mut refes = &mut self.root;
        for i in word.bytes() {
            let ret = refes.next[(i - b'a') as usize]
                .get_or_insert(Box::new(TrieNode::new(i)));
            refes = ret;
        }
        refes.is_end = true;
    }

    #[allow(unused)]
    fn search(&self, word: &str) -> bool {
        let refes = &self.root;
        Self::dfs(0, &word.bytes().collect::<Vec<u8>>(), refes)
    }

    #[allow(unused)]
    fn dfs(idx: usize, word: &[u8], node: &Box<TrieNode>) -> bool {
        let len_w: usize = word.len();
        const ANY: u8 = b'.';
        if idx == len_w {
            return node.is_end;
        }
        let ch = word[idx];
        match ch {
            ANY => {
                for ele in node.next.iter() {
                    if let Some(child) = ele.clone() {
                        if Self::dfs(idx + 1, word, child) {
                            return true;
                        }
                    }
                }
            }
            _ => match &node.next[ch as usize - 'a' as usize] {
                Some(child) => {
                    return Self::dfs(idx + 1, word, child);
                }
                None => return false,
            },
        }
        false
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let mut word_dictionary = WordDictionary::new();

        word_dictionary.add_word("bad");
        word_dictionary.add_word("dad");
        word_dictionary.add_word("mad");
        let mut ret = word_dictionary.search("pad"); // return False
        assert!(!ret);
        ret = word_dictionary.search("bad"); // return True
        assert!(ret);
        ret = word_dictionary.search(".ad"); // return True
        assert!(ret);
        ret = word_dictionary.search("b.."); // return True
        assert!(ret);
    }
}
