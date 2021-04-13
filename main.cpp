#include <iostream>
#include "printer.h"
#include <vector>
#include <set>
#include <ranges>

using namespace std;
int main() {
    vector<int> vi = {1, 2, 3, 4};
    set<int> si = {1, 2, 3, 4};
    vector<string> vs = {"a", "b", "c", "d"};

    cout << typeid(vi).name() << " " << is_specialization<decltype(vi), vector>::value << endl;
    cout << typeid(vs).name() << " " << is_specialization<decltype(vs), vector>::value << endl;
    cout << typeid(si).name() << " " << is_specialization<decltype(si), vector>::value << endl;


    std::cout << "Hello, World!" << std::endl;
    vector<int> v = {1, 2, 3, 5};
    stringstream ss;
    to_stream(ss, v);
    to_stream(ss, 1);
    cout << ss.str() << endl;

    vector<vector<int>> vv = {{1, 2}, {2, 3, 4}, {3, 4, 5, 6}};
    to_stream(cout, vv);
    cout << endl;

    vector<set<char>> vse = {{'1', 'c'}, {'a', 'b', 'c'}};
    to_stream(cout, vse);
    return 0;
}
