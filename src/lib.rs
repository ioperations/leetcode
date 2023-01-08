// #![feature(generic_associated_types)]
#![feature(type_alias_impl_trait)]
#![feature(generators, generator_trait)]
#![feature(slice_group_by)]
#![feature(test)]

mod classic;

mod leetcode {
    automod::dir!("src/leetcode/");
}
