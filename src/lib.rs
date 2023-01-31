// #![feature(generic_associated_types)]
#![feature(type_alias_impl_trait)]
#![feature(generators, generator_trait)]
#![feature(slice_group_by)]
#![feature(test)]
#![cfg_attr(feature = "cargo-clippy", warn(clippy::pedantic))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_lossless))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_possible_truncation))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_possible_wrap))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_precision_loss))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_precision_loss))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::cast_sign_loss))]
#![cfg_attr(feature = "cargo-clippy", allow(clippy::checked_conversions))]

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
    automod::dir!("src/leetcode/");
}
