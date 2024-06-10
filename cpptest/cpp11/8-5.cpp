#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <map>

using namespace std;

const int MaxObjectNum = 10;

class NonCopyable
{
public:
	NonCopyable(const NonCopyable&) = delete; // deleted
	NonCopyable& operator = (const NonCopyable&) = delete; // deleted
	NonCopyable() = default;   // available
};

template<typename T>
class ObjectPool : NonCopyable {
    template<typename... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
    ObjectPool() : needClear(false) {}
    ~ObjectPool() {
        needClear = true;
    }

    template<typename... Args>
    void Init(size_t num, Args&&... args) {
        if (num <= 0 || num > MaxObjectNum) {
            throw std::logic_error("object num out of range.");
        }

        auto constructName = typeid(Constructor<Args...>).name();
        for (size_t i = 0; i < num; ++i) {
            m_object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName](T* p) {
                m_object_map.emplace(std::move(constructName),  std::shared_ptr<T>(p));
            }));

        }
    }

    template<typename... Args>
    std::shared_ptr<T> Get() {
        string constructName = typeid(Constructor<Args...>).name();
        auto range = m_object_map.equal_range(constructName);
        for (auto it = range.first; it != range.second; ++it) {
            auto ptr = it->second;
            m_object_map.erase(it);
            return ptr;
        }

        return nullptr;
    }

private:
    multimap<string, std::shared_ptr<T>> m_object_map;
    bool needClear;
};

struct BigObject {
    BigObject() {
        std::cout << "BigObject()" << std::endl;   
    }
    BigObject(int a) {
        std::cout << "BigObject(int)" << std::endl;
    }
    BigObject(const int& a, const int& b) {
        std::cout << "BigObject(const int&, const int&)" << std::endl;
    }

    void Print(const string& str) {
        cout << str << endl;
    }
};

void Print(shared_ptr<BigObject> p, const string& str) {
    if (p) {
        p->Print(str);
    } else {
        cout << "Invalid object" << endl;
    }
}

void TestObjectPool() {
    ObjectPool<BigObject> pool;
    pool.Init(2);
    {
        auto p1 = pool.Get();
        Print(p1, "p1");
        auto p2 = pool.Get();
        Print(p2, "p2");
        auto p3 = pool.Get();
        Print(p3, "p3");
    }
    auto p = pool.Get();
    auto p2 = pool.Get();
    Print(p, "p");
    Print(p2, "p2");

    pool.Init(2, 1);
    auto p4 = pool.Get<int>();
    Print(p4, "p4");
    pool.Init(2, 1, 2);
    auto p5 = pool.Get<int, int>();
    Print(p5, "p5");
}

int main() {
    TestObjectPool();
    return 0;
}