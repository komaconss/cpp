#include <iostream>
using namespace std;

template <class... T>
void f(T... args) {
    cout << sizeof...(args) << endl;
}

int main() {
    f();
    f(1, 2);
    f(1, 2, "");
    return 0;
}