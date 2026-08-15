use proc_macro::TokenStream;

mod hello;
mod lru;

#[proc_macro_derive(Hello)]
pub fn add_struct_output(token_stream: TokenStream) -> TokenStream {
    hello::impl_hello_macro(token_stream)
}

// 2. 必须在 Crate 根部定义这个带有属性标记的入口函数
#[proc_macro_attribute]
pub fn lru_cache(attr: TokenStream, item: TokenStream) -> TokenStream {
    // 3. 将其直接转发给子模块的内部实现
    lru::lru_cache_impl(attr, item)
}
