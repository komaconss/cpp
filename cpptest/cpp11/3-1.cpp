#include <iostream>
#include <type_traits>
#include <memory>
using namespace std;

template <class T>
struct Construct {
    typedef typename std::remove_reference<T>::type U;
    Construct() : m_ptr(new U) {
        cout << "Construct" << endl;
    }

    typename std::add_lvalue_reference<U>::type Get() {
        return *m_ptr.get();
    }

private:
    std::unique_ptr<U> m_ptr;
};

int main() {
    Construct<int> c;
    cout << c.Get() << endl;
}