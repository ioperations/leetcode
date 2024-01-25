// 实现类似rocksdb的一系列iterator，讲解如何再rust中用gat实现零开销的aync trait
/*


TestIterator: 残生一个有序的kv序列
ConcatIterator：将多个iterator的序列拼接起来
*/
/*


KvIterator是将会给所有iterators实现的一个trait。用户可以调用。next来将迭代器移动到下一个位置
*/

/*
/// 下面这个trait会编译不过，提示async暂时不支持再trait中使用
pub trait KvIerator {
    /// Get the next iterm from the iterator
    async fn next(&mut self) -> Option<(&[u8], &[u8])>;
}
*/

use core::future::Future;
use std::usize;

// 编译器没有支持async trait，本质上是因为不同的impl Kviterator的.next函数返回的
// Future类型是不同的。这个问题可有用associated type简单地解决：
/// 这里就引入一个问题：&‘lifetime [u8]需要有一个生命周期，这个生命周期应该怎么写?
/// 从道理上来讲, 'lifetime和next的&mut self生命周期一致，所以他应该是NextFuture
/// 本身的一个范型。再rust里面怎么表达这件事情? 显然这就需要genenric associated
/// type了，开启gat编译选项之后
/*
pub trait KvIterator {
    type NextFuture: Future<Output = Option<(&[u8], &[u8])>>;

    /// Get the next item from the iterator.
    fn next(&mut self) -> Self::NextFuture;
}
*/

/*
NextFuture 是由 next 函数返回的，而一个正常实现的 next 函数，只能返回和 &mut self 生命周期相同的引用。Rust 的 trait 可以实现在一个引用上 (e.g., impl <'a> Iterator for &'a mut SomeIterator)。如果 Self (在上面的例子里，&'a mut SomeIterator) 本身的生命周期比这个引用还要短，就不可能返回这样一个 NextFuture 了。

所以在这里，我们需要加一个 where Self: 'a，保证 Self 的生命周期至少和 NextFuture 的 'a 一样长。
*/

pub trait KvIterator {
    type NextFuture<'a>: Future<Output = Option<(&'a [u8], &'a [u8])>>
    where
        Self: 'a;

    /// Get the next item from the iterator.
    fn next(&mut self) -> Self::NextFuture<'_>;
}

#[allow(unused)]
pub struct TestIterator {
    idx: usize,
}

impl KvIterator for TestIterator {
    type NextFuture<'a> = impl Future<Output = Option<(&'a [u8], &'a [u8])>>;
    /*既然 next 返回一个函数，NextFuture 的类型怎么写？众所周知，Rust 的函数是写不出类型的。
    这里就要开启一个 feature，让编译器自动推导 Future 的具体类型*/
    fn next(&mut self) -> Self::NextFuture<'_> {
        /*next 里面应该怎么写逻辑？next 返回的是一个 Future，并不是常见的 async fn。
        答案很简单，用 async move 返回一个闭包。*/
        async move { Some((b"key".as_slice(), b"value".as_slice())) }
    }
}

#[allow(unused)]
pub struct TestIteratorV2 {
    idx: usize,
    to_idx: usize,
    key: Vec<u8>,
    value: Vec<u8>,
}

pub struct TestIteratorV3 {
    idx: usize,
    to_idx: usize,
    key: Vec<u8>,
    value: Vec<u8>,
}

#[allow(unused)]
impl TestIteratorV3 {
    pub fn new(from_idx: usize, to_idx: usize) -> Self {
        Self {
            idx: from_idx,
            to_idx,
            key: Vec::new(),
            value: Vec::new(),
        }
    }
}
impl KvIterator for TestIteratorV3 {
    type NextFuture<'a>
    = impl Future<Output = Option<(&'a [u8], &'a [u8])>> where Self: 'a;

    fn next(&mut self) -> Self::NextFuture<'_> {
        async move {
            if self.idx >= self.to_idx {
                return None;
            }

            // Zero-allocation key value manipulation

            self.key.clear();
            // write!(&mut self.key, "key_{:05}", self.idx).unwrap();
            for i in format!("key_{:05}", self.idx).as_bytes() {
                self.key.push(*i);
            }

            self.value.clear();
            for i in format!("value_{:05}", self.idx).as_bytes() {
                self.value.push(*i);
            }
            // write!(&mut self.value, "value_{:05}", self.idx).unwrap();

            self.idx += 1;
            Some((&self.key, &self.value))
        }
    }
}

#[tokio::test]
async fn test_iteratorv3() {
    let mut iter = TestIteratorV3::new(0, 10);
    while let Some((key, value)) = iter.next().await {
        println!("{:?} {:?}", key, value);
    }
}

pub struct ConcatIterator<Iter: KvIterator> {
    iters: Vec<Iter>,
    current_idx: usize,
}


#[allow(unused)]
impl<Iter: KvIterator> ConcatIterator<Iter> {
    pub fn new(iters: Vec<Iter>) -> Self {
        Self {
            iters,
            current_idx: 0,
        }
    }
}

impl<Iter:KvIterator> KvIterator for ConcatIterator<Iter> {
    type NextFuture <'a> = 
    impl Future<Output = Option<(&'a [u8],&'a [u8])>> where Self :'a;
    fn next(&mut self) -> Self::NextFuture<'_> {
        async move{
            loop {
                if self.current_idx >= self.iters.len(){
                    return None;
                }

                let iter = &mut self.iters[self.current_idx];
                match iter.next().await {
                    b @ Some(_)=> {
                        return b;
                    }
                    None=>{
                        self.current_idx+=1;
                    }
                }
            }

        }
    }
    
}

#[tokio::test]
async fn test_iterator_v3() {
    let iter1 = TestIteratorV3::new(0, 5);
    let iter2 = TestIteratorV3::new(5, 10);
    let mut concat_iter = ConcatIterator::new(vec![iter1, iter2]);

    while let Some((key, value)) = concat_iter.next().await {
        println!(
            "{:?} {:?}",
            std::str::from_utf8(key).unwrap(),
            std::str::from_utf8(value).unwrap()
        );
    }
}
