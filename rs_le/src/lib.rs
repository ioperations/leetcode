use proc_macro::TokenStream;

use quote::quote;
use syn::{parse_macro_input, DeriveInput};

fn impl_hello_macro(ast: &syn::DeriveInput) -> TokenStream {
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

#[proc_macro_derive(Hello)]
pub fn add_struct_output(token_stream: TokenStream) -> TokenStream {
    let input = parse_macro_input!(token_stream as DeriveInput);
    impl_hello_macro(&input)
}
