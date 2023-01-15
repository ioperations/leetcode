#[allow(unused)]
fn fibonacci(n: u32) -> u32 {
    if n == 0 || n == 1 {
        1
    } else {
        let mut i = 0;
        let mut sum: i32 = 0;
        let mut last: i32 = 0;
        let mut curr: i32 = 1;
        while i < n - 1 {
            sum = {
                if let Some(sum) = last.checked_add(curr) {
                    sum
                } else {
                    last
                }
            };
            last = curr;
            curr = sum;
            i += 1;
        }
        sum as u32
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use futures::future::join_all;
    use std::sync::mpsc::channel;
    use threadpool::ThreadPool;
    extern crate test;

    static BENCH_SIZE: u32 = 1000;

    #[bench]
    fn bench_sync(b: &mut test::Bencher) {
        let value: u32 = (0..BENCH_SIZE)
            .map(fibonacci)
            .reduce(|acc, e| {
                if let Some(res) = acc.checked_add(e) {
                    res
                } else {
                    acc
                }
            })
            .unwrap();
        println!("value is  {value}");

        b.iter(|| {
            let res = (0..BENCH_SIZE)
                .map(fibonacci)
                .reduce(|acc, e| {
                    if let Some(res) = acc.checked_add(e) {
                        res
                    } else {
                        acc
                    }
                })
                .unwrap();
            assert_eq!(res, value);
        });
    }

    use rayon::prelude::*;

    #[bench]
    fn bench_simd_sync(b: &mut test::Bencher) {
        let value: u32 = (0..BENCH_SIZE).into_par_iter().map(fibonacci).reduce(
            || (0_u32),
            |acc, e| {
                if let Some(res) = acc.checked_add(e) {
                    res
                } else {
                    acc
                }
            },
        );
        println!("value is  {value}");

        b.iter(|| {
            let res = (0..BENCH_SIZE).into_par_iter().map(fibonacci).reduce(
                || (0),
                |acc, e| {
                    if let Some(res) = acc.checked_add(e) {
                        res
                    } else {
                        acc
                    }
                },
            );
            assert_eq!(res, value);
        });
    }

    #[bench]
    fn bench_actor(b: &mut test::Bencher) {
        #[allow(unused)]
        use actix::prelude::*;

        struct Fibonacci(pub u32);

        impl Message for Fibonacci {
            type Result = Result<u32, ()>;
        }

        struct SyncActor;

        impl Actor for SyncActor {
            type Context = SyncContext<Self>;
        }

        impl Handler<Fibonacci> for SyncActor {
            type Result = Result<u32, ()>;

            fn handle(&mut self, msg: Fibonacci, _: &mut Self::Context) -> Self::Result {
                Ok(fibonacci(msg.0))
            }
        }

        {
            let value: u32 = (0..BENCH_SIZE)
                .map(fibonacci)
                .reduce(|acc, e| {
                    if let Some(res) = acc.checked_add(e) {
                        res
                    } else {
                        acc
                    }
                })
                .unwrap();

            println!("value is  {value}");
            let system = System::new();
            b.iter(|| {
                system.block_on(async {
                    let addr = SyncArbiter::start(4, || SyncActor);
                    let res = join_all((0..BENCH_SIZE).map(|i| addr.send(Fibonacci(i))))
                        .await
                        .into_iter()
                        .map(|v| v.unwrap().unwrap())
                        .reduce(|acc, e| {
                            if let Some(res) = acc.checked_add(e) {
                                res
                            } else {
                                acc
                            }
                        })
                        .unwrap();
                    assert_eq!(res, value);
                });
            });
        }
    }

    #[ignore = "FIXME: 🦀 do not know why, the result is not match!!!"]
    #[bench]
    fn bench_threadpool(b: &mut test::Bencher) {
        let value: u32 = (0..BENCH_SIZE)
            .map(fibonacci)
            .reduce(|acc, e| {
                if let Some(res) = acc.checked_add(e) {
                    res
                } else {
                    acc
                }
            })
            .unwrap();

        println!("value is  {value}");

        let n_workers = 4;
        let pool = ThreadPool::new(n_workers);
        b.iter(|| {
            let (tx, rx) = channel();
            for i in 0..BENCH_SIZE {
                let tx = tx.clone();
                pool.execute(move || {
                    let fib = fibonacci(i);
                    tx.send(fib)
                        .expect("channel will be there waiting for the pool");
                });
            }

            assert_eq!(
                rx.iter()
                    .take(BENCH_SIZE as usize)
                    .reduce(|acc, e| {
                        if let Some(res) = acc.checked_add(e) {
                            res
                        } else {
                            acc
                        }
                    })
                    .unwrap(),
                value
            );
        });
    }
}
