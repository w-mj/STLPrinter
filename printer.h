#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <iterator>
#include <tuple>
#include <vector>
#include <ostream>
#include <set>
#include <stack>
#include <map>
#include <forward_list>
#include <list>
#include <unordered_map>
#include <unordered_set>

template <typename T, typename = void>
struct is_iterable_v : std::false_type {};

template <typename T>
struct is_iterable_v<T, std::void_t<
        decltype(std::begin(std::declval<T>())),
        decltype(std::end(std::declval<T>()))
    >
> : std::true_type {};

template<typename T>
concept Iterable = is_iterable_v<T>::value;

template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: std::true_type {};

template<typename T, template<typename...>class... Types>
constexpr bool is_instance() {
    return (is_specialization<T, Types>::value || ...);
}

template<typename T>
concept SetContainer = is_instance<T, std::set, std::multiset, std::unordered_set, std::unordered_multiset>();

template<typename T>
concept MapContainer = is_instance<T, std::map, std::multimap, std::unordered_map, std::unordered_multimap>();

template<typename T>
concept AssociateContainer = MapContainer<T> || SetContainer<T>;

template<typename T>
concept ListContainer = is_instance<T, std::vector, std::forward_list, std::list, std::deque>();

template<typename T>
concept IterableContainer = ListContainer<T> || MapContainer<T> || SetContainer<T>;

template <typename>
struct bracket {};

struct Parentheses {
    static constexpr char prefix = '(';
    static constexpr char postfix = ')';
};


template<typename T> requires ListContainer<T>
struct bracket<T> {
    static constexpr char prefix = '[';
    static constexpr char postfix = ']';
};

template<typename T> requires AssociateContainer<T>
struct bracket<T> {
    static constexpr char prefix = '{';
    static constexpr char postfix = '}';
};



/* declarations */
//template<IterableContainer T> std::ostream& iterable_to_stream(std::ostream &ss, const T& v);
template<IterableContainer T> std::ostream& operator<<(std::ostream &ss, const T& v);
template<typename K, typename V> std::ostream& operator<<(std::ostream &ss, const std::pair<K, V>& v);


/* defines */
template<IterableContainer T,
        typename I = decltype(*std::declval<T>().begin()),
        typename F = std::ostream&(*)(std::ostream&, const I &)>
std::ostream& iterable_to_stream(std::ostream &ss, const T& v, const std::string& delimiter=",",
                                 F op = [](std::ostream &ss, const I& v)->std::ostream&{ return ss << v; }){
    bool not_begin = false;
    for (const auto& item: v) {
        if (not_begin) [[likely]] {
            ss << delimiter;
        } else [[unlikely]] {
            not_begin = true;
        }
//        op(ss, item);
        std::invoke(op, ss, item);
    }
    return ss;
}


template<IterableContainer T>
std::ostream& operator<<(std::ostream &ss, const T& v) {
    using namespace std;
    ss << bracket<T>::prefix;
    iterable_to_stream(ss, v);
    ss << bracket<T>::postfix;
    return ss;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream &ss, const std::pair<K, V>& v) {
    return ss << "(" << v.first << "->" << v.second << ")";
}
