// #![feature(generic_associated_types)]
#![feature(test)]

#[cfg(test)]
use ctor::ctor;

#[cfg(test)]
use tracing_subscriber::{fmt, layer::SubscriberExt, util::SubscriberInitExt};

#[cfg(test)]
#[ctor]
fn register_tracing() {
    tracing_subscriber::registry().with(fmt::layer()).init();
}

mod classic;

mod leetcode {
    automod::dir!("rs/leetcode/");
}
