
#pragma once
#include <iterator>
#include <type_traits>
#include <utility>

template <typename T, typename = void>
struct IsIterator : std::false_type {};

template <typename T>
struct IsIterator<T, std::void_t<decltype(std::begin(std::declval<T&>())),
                                 decltype(std::end(std::declval<T&>())),
                                 std::enable_if_t<!std::is_same_v<std::decay_t<T>, std::string>>>>
    : std::true_type {};

template <typename T, typename Func>
void DfsForEach(T&& list_or_item, Func func) {
    if constexpr (IsIterator<T>::value) {
        // 使用 std::begin 确保在没有 ADL 的情况下也能找到定义
        using std::begin;
        using std::end;
        for (auto& item : list_or_item) {
            DfsForEach(item, func);
        }
    } else {
        func(std::forward<T>(list_or_item));
    }
}
