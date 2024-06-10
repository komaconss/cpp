#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
struct GetLeftSize : std::integral_constant<int, 1> {};

int main() {
    cout << GetLeftSize<int>::value << endl;

    return 0;
}