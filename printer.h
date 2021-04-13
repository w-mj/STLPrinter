#pragma once
#include <string>
#include <sstream>
#include <iterator>
//#include <experimental/iterator>
#include <tuple>
#include <vector>
#include <ostream>
#include <set>

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

template<typename>
struct bracket {};

template<typename T, typename A>
struct bracket<std::vector<T, A>> {
    static constexpr char prefix = '[';
    static constexpr char postfix = ']';
};

template<typename T, typename A>
struct bracket<std::set<T, A>> {
    static constexpr char prefix = '{';
    static constexpr char postfix = '}';
};

template<typename T>
void to_stream(std::ostream &ss, const T& v) {
    ss << v;
}

template<Iterable T>
void to_stream(std::ostream &ss, const T& v) {
    using namespace std;
    ss << bracket<T>::prefix;
    vector<string> transform_inner;
    bool begin = true;
    //TODO: 使用rnges
    for (const auto& item: v) {
        if (!begin) /*TODO: [[likely]]*/ {
            ss << ',';
        } else {
            begin = false;
        }
        to_stream(ss, item);
    }
//    copy(v.begin(), v.end(), experimental::make_ostream_joiner(ss, ","));
    ss << bracket<T>::postfix;
}
