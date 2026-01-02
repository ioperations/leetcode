
#pragma once
#include <iterator>
#include <type_traits>
#include <utility>

using namespace std;

template <typename T, typename = void>
struct IsIterator : std::false_type {};

template <typename T>
struct IsIterator<T, std::void_t<decltype(std::begin(std::declval<T&>())),
                                 decltype(std::end(std::declval<T&>()))>>
    : std::true_type {};

template <typename T, typename Func>
void DfsForEach(T&& list_or_item, Func func) {
    if constexpr (IsIterator<T>::value || !std::is_same_v<std::string, T>) {
        for (auto& item : list_or_item) {
            DfsForEach(item, func);
        }
    } else {
        func(std::forward<T>(list_or_item));
    }
}
