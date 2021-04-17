//
// Created by WMJ on 2021/4/17.
//

#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <functional>
using namespace std;

template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: std::true_type {};

template<typename T, template<typename...>class... Types>
constexpr inline bool is_instance() {
    return (is_specialization<T, Types>::value || ...);
}

template<typename T> concept VSM = is_instance<T, vector, set, map>();

template<VSM T>
bool is_v_s(const T& a) {
    return true;
}

template<typename T>
bool is_v_s(const T& a) {
    return false;
}

#include <iostream>
#include <vector>
#include <functional>
template<typename T,
        typename IN = decltype(*std::declval<T>().begin()),
        typename FT = function<ostream&(ostream&, const IN&)>
        >
void func(ostream& ss, const T& v,
              FT op = [](ostream& os, const IN&v)->ostream&{ return os << v; }) {
    for (const auto& i: v) {
        std::invoke(op, ss, i);
    }
}

int main() {
    vector<int> vec = {1, 2, 3, 4};
    func(cout, vec);
    return 0;
}