use proc_macro::TokenStream;

use quote::quote;
use syn::{parse_macro_input, DeriveInput};

pub fn impl_hello_macro(token_stream: TokenStream) -> TokenStream {
    let ast = parse_macro_input!(token_stream as DeriveInput);
    let name = &ast.ident;
    let generated = quote! {
        impl #name {
            fn hello_macro() -> String {
                format!("Hello, Macro! My name is {}!", stringify!(#name))
            }
        }
    };
    generated.into()
}
