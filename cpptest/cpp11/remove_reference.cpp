#include <iostream>
#include <type_traits>
#include <memory>
using namespace std;

template <typename T>
struct Construct {
    typedef typename std::remove_reference<T>::type U;
    Construct() : m_ptr(new U) {}
    typename std::add_lvalue_reference<U>::type
    Get() const {
        return *m_ptr.get();
    }
private:
    std::unique_ptr<U> m_ptr;
};

int main() {
    Construct<int> c;
    int a = c.Get();
    cout << a << endl;

    typedef std::conditional<(sizeof(long long) > sizeof(long double)),
        long long, long double>::type BigFloat;
    cout << typeid(BigFloat).name() << endl;

    return 0;
}