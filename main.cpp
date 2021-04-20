#include <iostream>
#include "printer.h"
#include <vector>
#include <set>
#include <ranges>
#include <map>

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
    ss << v;
    ss << 1;
//    to_stream(ss, v);
//    to_stream(ss, 1);
    cout << ss.str() << endl;

    vector<vector<int>> vv = {{1, 2}, {2, 3, 4}, {3, 4, 5, 6}};
    cout << vv << endl;

    vector<set<char>> vse = {{'1', 'c'}, {'a', 'b', 'c'}};
    cout << vse << endl;

    map<string, vector<set<char>>> m;
    m.emplace("aaa", vse);
    m.emplace("aaa", vse);
    m.emplace("bbb", vse);
    m.emplace("ccc", vse);

    cout << m << endl;

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << q << endl;
    cout << s << endl;
    return 0;
}
