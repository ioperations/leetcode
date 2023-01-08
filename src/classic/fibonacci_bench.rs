#[allow(unused)]
fn fibonacci(n: u32) -> u32 {
    if n == 0 || n == 1 {
        1
    } else {
        let mut i = 0;
        let mut sum = 0;
        let mut last = 0;
        let mut curr = 1;
        while i < n - 1 {
            sum = last + curr;
            last = curr;
            curr = sum;
            i += 1;
        }
        sum
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use futures::future::join_all;
    use std::sync::mpsc::channel;
    use threadpool::ThreadPool;
    extern crate test;

    static BENCH_SIZE: u32 = 20;

    #[bench]
    fn bench_sync(b: &mut test::Bencher) {
        let value: u32 = (0..BENCH_SIZE)
            .map(fibonacci)
            .reduce(|acc, e| acc + e)
            .unwrap();

        b.iter(|| {
            let res = (0..BENCH_SIZE)
                .map(fibonacci)
                .reduce(|acc, e| acc + e)
                .unwrap();
            assert_eq!(res, value);
        })
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
                .reduce(|acc, e| acc + e)
                .unwrap();

            let system = System::new();
            b.iter(|| {
                system.block_on(async {
                    let addr = SyncArbiter::start(2, || SyncActor);
                    let res = join_all((0..BENCH_SIZE).map(|i| addr.send(Fibonacci(i))))
                        .await
                        .into_iter()
                        .map(|v| v.unwrap().unwrap())
                        .reduce(|acc, e| acc + e)
                        .unwrap();
                    assert_eq!(res, value);
                });
            })
        }
    }

    #[bench]
    fn bench_threadpool(b: &mut test::Bencher) {
        let value: u32 = (0..BENCH_SIZE)
            .map(fibonacci)
            .reduce(|acc, e| acc + e)
            .unwrap();
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
                    .reduce(|acc, e| acc + e)
                    .unwrap(),
                value
            );
        })
    }
}
