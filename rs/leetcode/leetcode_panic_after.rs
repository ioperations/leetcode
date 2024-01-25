use std::{sync::mpsc, thread, time::Duration};

#[allow(unused)]
pub fn panic_after<T, F>(d: Duration, f: F) -> T
where
    T: Send + 'static,
    F: FnOnce() -> T,
    F: Send + 'static,
{
    let (done_tx, done_rx) = mpsc::channel();
    let handle = thread::spawn(move || {
        let val = f();
        done_tx.send(()).expect("Unable to send completion signal");
        val
    });

    match done_rx.recv_timeout(d) {
        Ok(()) => handle.join().expect("Thread panicked"),
        err @ Err(_) => {
            err.err();
            panic!("Thread took too long",)
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[should_panic(expected = "Thread took too long")]
    #[test]
    fn test_panic() {
        let test = || thread::sleep(Duration::new(10, 0));

        panic_after(Duration::new(2, 0), test);
    }
}
