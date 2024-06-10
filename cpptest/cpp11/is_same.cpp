#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << is_same<int, int>::value << endl;
    cout << is_same<int, float>::value << endl;

    return 0;
}