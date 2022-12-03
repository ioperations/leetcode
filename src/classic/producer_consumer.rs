use std::sync::{Arc, Condvar, Mutex};
use std::thread;
use std::time;

struct Producer {
    cvar: Arc<(Mutex<bool>, Condvar)>,
}

impl Producer {
    #[allow(unused)]
    pub fn new(cvar: Arc<(Mutex<bool>, Condvar)>) -> Producer {
        Producer { cvar }
    }

    pub fn get_cvar(&self) -> &Arc<(Mutex<bool>, Condvar)> {
        &self.cvar
    }

    #[allow(unused)]
    pub fn start(&self) {
        let pair = self.cvar.clone();
        thread::spawn(move || loop {
            let &(ref lock, ref cvar) = &*pair;
            std::thread::sleep(time::Duration::from_millis(100));
            let mut status = lock.lock().unwrap();
            *status = true;
            cvar.notify_all();
            *status = false;
        });
    }
}

struct Consumer<'a> {
    name: String,
    producer: &'a Producer,
}

impl<'a> Consumer<'a> {
    #[allow(unused)]
    pub fn new(name: String, producer: &'a Producer) -> Consumer<'a> {
        Consumer { name, producer }
    }

    #[allow(unused)]
    pub fn start(&self) {
        let prod = self.producer.get_cvar().clone();
        let name = self.name.clone();
        thread::spawn(move || {
            let &(ref lock, ref cvar) = &*prod;
            let mut fetched = lock.lock().unwrap();
            loop {
                fetched = cvar.wait(fetched).unwrap();
                println!("Recieved {}", name);
            }
        });
    }
}

#[cfg(test)]
mod testmod {
    use super::*;

    #[test]
    fn producer_consumer_test() {
        use std::time;
        let p = Producer::new(Arc::new((Mutex::new(false), Condvar::new())));
        let c = Consumer::new("c1".to_string(), &p);
        let c2 = Consumer::new("c2".to_string(), &p);
        p.start();
        c.start();
        c2.start();
        std::thread::sleep(time::Duration::from_millis(100));
    }
}
