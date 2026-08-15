use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, FnArg, ItemFn, LitInt, Pat, ReturnType};

pub fn lru_cache_impl(attr: TokenStream, item: TokenStream) -> TokenStream {
    // 1. 解析缓存容量大小
    let cache_size = if attr.is_empty() {
        quote! { 128 }
    } else {
        let lit = parse_macro_input!(attr as LitInt);
        quote! { #lit }
    };

    let input_fn = parse_macro_input!(item as ItemFn);
    let vis = &input_fn.vis;
    let sig = &input_fn.sig;
    let body = &input_fn.block;

    // 2. 提取函数的入参类型和返回类型，用于显式定义 Static 字典的类型
    let mut key_types = Vec::new();
    let mut arg_names = Vec::new();

    for arg in &sig.inputs {
        if let FnArg::Typed(pat_type) = arg {
            if let Pat::Ident(pat_ident) = &*pat_type.pat {
                let name = &pat_ident.ident;
                let ty = &pat_type.ty;
                arg_names.push(quote! { #name.clone() });
                key_types.push(quote! { #ty });
            }
        }
    }

    // 如果没有返回类型，默认是 () 单元类型
    let return_type = match &sig.output {
        ReturnType::Default => quote! { () },
        ReturnType::Type(_, ty) => quote! { #ty },
    };

    // 组合成显式的 Key 格式（例如：(u32, u32)）
    let key_tuple_type = quote! { ( #(#key_types),* ) };
    let key_tuple_val = quote! { ( #(#arg_names),* ) };

    // 3. 生成宏代码：使用标准库的 HashMap 并由 Vec 辅助维护访问顺序（实现 LRU）
    let expanded = quote! {
        #vis #sig {
            static CACHE: std::sync::OnceLock<std::sync::Mutex<(std::collections::HashMap<#key_tuple_type, #return_type>, Vec<#key_tuple_type>)>> = std::sync::OnceLock::new();

            let cache_lock = CACHE.get_or_init(|| {
                std::sync::Mutex::new((std::collections::HashMap::new(), Vec::new()))
            });

            let cache_key = #key_tuple_val;

            // 第一步：检查缓存命中
            {
                let mut guard = cache_lock.lock().unwrap();
                let (map, order) = &mut *guard;
                if let Some(cached_val) = map.get(&cache_key) {
                    // LRU 逻辑：将当前 Key 移到队列末尾（表示最近使用过）
                    if let Some(pos) = order.iter().position(|k| k == &cache_key) {
                        order.remove(pos);
                    }
                    order.push(cache_key.clone());
                    return cached_val.clone();
                }
            }

            // 第二步：缓存未命中，执行原本的业务逻辑
            let computed_val = (|| #body)();

            // 第三步：将新结果存入缓存，并执行 LRU 淘汰机制
            {
                let mut guard = cache_lock.lock().unwrap();
                let (map, order) = &mut *guard;

                // 如果超过设定的阈值，淘汰最早未使用的元素
                if map.len() >= #cache_size {
                    if !order.is_empty() {
                        let oldest_key = order.remove(0);
                        map.remove(&oldest_key);
                    }
                }

                map.insert(cache_key.clone(), computed_val.clone());
                order.push(cache_key);
            }

            computed_val
        }
    };

    expanded.into()
}
