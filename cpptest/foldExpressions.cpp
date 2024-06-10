#include <iostream>
using namespace std;

template<typename ...Args>
auto sum(Args ...args) {
    return (args + ...);
}

int main() {
    std::cout << "C++ Compiler Version: " << __cplusplus << std::endl;
    cout << sum(1, 2, 3, 4, 5) << endl;
    cout << sum(1, 2, 3) << endl;
    return 0;
}