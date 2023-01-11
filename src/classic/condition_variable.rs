mod tests {

    #[test]
    fn condvar_test() {
        use std::sync::{Arc, Condvar, Mutex};
        use std::thread;
        let pair = Arc::new((Mutex::new(false), Condvar::new()));
        let pair2 = pair.clone();

        // Inside of our lock, spawn a new thread, and then wait for it to start.
        thread::spawn(move || {
            let (lock, cvar) = &*pair2;
            let mut started = lock.lock().unwrap();
            *started = true;
            // We notify the condvar that the value has changed.
            cvar.notify_one();
        });

        // Wait for the thread to start up.
        let (lock, cvar) = &*pair;
        let mut started = lock.lock().unwrap();
        while !*started {
            started = cvar.wait(started).unwrap();
        }
        println!("condition varialbe ok");
    }

    #[test]
    fn condition_variable_test() {
        use std::sync::Arc;
        use std::sync::Condvar;
        use std::sync::Mutex;
        use std::thread;
        use std::time;
        let pair = Arc::new((Mutex::new(false), Condvar::new()));

        let pair2 = pair.clone();
        println!("here ");
        let job_consumer = thread::spawn(move || {
            let (started, cond) = &*pair2;

            let mut lock = started.lock().unwrap();
            while !*lock {
                lock = cond.wait(lock).unwrap();
            }
            println!("get condition true");
        });

        let job_producer = thread::spawn(move || {
            let (started, cond) = &*pair;
            for _ in 0..1 {
                println!("before sleep ...");
                thread::sleep(time::Duration::from_millis(1));
                println!("after sleep ...");

                let mut started = started.lock().unwrap();
                *started = true;
                cond.notify_one();
            }
        });

        job_consumer.join().unwrap();
        println!("consumer exit");
        job_producer.join().unwrap();
    }

    #[derive(Debug, PartialEq)]
    #[allow(unused)]
    struct Protocol {
        ok: bool,
        id: i32,
        type_str: &'static str,
        message: String,
    }

    impl Protocol {
        #[allow(unused)]
        fn new() -> Self {
            Self {
                ok: false,
                id: 0,
                type_str: "",
                message: String::new(),
            }
        }
    }

    #[test]
    fn communication_through_condition_variable() {
        use std::sync::Arc;
        use std::sync::Condvar;
        use std::sync::Mutex;
        use std::thread;
        use std::time;

        let pair = Arc::new((Mutex::new(Protocol::new()), Condvar::new()));

        let pair2 = pair.clone();
        let job_consumer = thread::spawn(move || {
            let (started, cond) = &*pair2;
            let mut lock = started.lock().unwrap();
            while !lock.ok {
                lock = cond.wait(lock).unwrap();
            }
            let mut obj = Protocol::new();
            {
                obj.ok = true;
                obj.id = 1;
                obj.type_str = "hello";
                obj.message = String::from("world");
            }
            assert_eq!(*lock, obj);
            println!("Protocol is {:?}", *lock);
            println!("get condition true");
        });
        let job_producer = thread::spawn(move || {
            let (started, cond) = &*pair;
            for _ in 0..1 {
                println!("before sleep");
                thread::sleep(time::Duration::from_millis(1));
                println!("after sleep");
                let mut started = started.lock().unwrap();
                started.ok = true;
                {
                    started.id = 1;
                    started.type_str = "hello";
                    started.message = String::from("world");
                }
                cond.notify_one();
            }
        });
        job_consumer.join().unwrap();
        println!("consumer exit ok");
        job_producer.join().unwrap();
    }

    #[test]
    fn new_test() {
        use std::sync::Arc;
        use std::sync::Condvar;
        use std::sync::Mutex;
        use std::thread;
        use std::time;

        let pair = Arc::new((Mutex::new(false), Condvar::new()));
        let pair2 = pair.clone();
        let job_cosumer = thread::spawn(move || {
            let (started, cond) = &*pair2;
            let mut lock = started.lock().unwrap();

            while !*lock {
                lock = cond.wait(lock).unwrap();
            }
            println!("get condition true");
        });
        let job_producer = thread::spawn(move || {
            let (started, cond) = &*pair;
            for _ in 0..1 {
                println!(" before sleep ...");
                thread::sleep(time::Duration::from_millis(1));
                println!("after sleep ...");
                let mut started = started.lock().unwrap();
                *started = true;
                cond.notify_one();
            }
        });
        job_cosumer.join().unwrap();
        println!("consumer exit");
        job_producer.join().unwrap();
    }
}
