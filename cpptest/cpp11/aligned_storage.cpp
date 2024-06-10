#include <iostream>
#include <type_traits>
using namespace std;

struct A {
    int avg;
    A (int a, int b) : avg((a + b) / 2) {}
};
typedef std::aligned_storage<sizeof(A), alignof(A)>::type A_storage;

int main() {
    A_storage a, b;
    new (&a) A(1, 2);
    b = a;
    cout << reinterpret_cast<A&>(b).avg << endl;
    
    return 0;
}