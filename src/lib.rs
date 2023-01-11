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

mod classic;

mod leetcode {
    automod::dir!("src/leetcode/");
}
