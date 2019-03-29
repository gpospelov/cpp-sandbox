#include <iostream>
#include <memory>

class A
{
public:
    A() {
        std::cout << "A()" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B
{
public:
    B() {
        std::cout << "B()" << std::endl;
    }
    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

class C
{
public:
    C() {
        std::cout << "C()" << std::endl;
    }
    ~C() {
        std::cout << "~C()" << std::endl;
    }
};

class Base
{
public:
    Base() : m_a(std::make_unique<A>()),  m_b(std::make_unique<B>()){
        std::cout << "Base()" << std::endl;
    }
    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }
    std::unique_ptr<A> m_a;
    std::unique_ptr<B> m_b;
};

class Derived : public Base
{
public:
    Derived() : m_c(std::make_unique<C>()){
        std::cout << "Derived()" << std::endl;
    }
    virtual ~Derived() {
        std::cout << "~Derived()" << std::endl;
    }
    std::unique_ptr<C> m_c;
};

int main()
{
    std::cout << "Hello Gennady" << std::endl;
    std::cout << "--- before construction" << std::endl;
    std::unique_ptr<Derived> d = std::make_unique<Derived>();
    std::cout << "--- before destruction" << std::endl;
    d.reset();
    std::cout << "--- after destruction" << std::endl;
    return 0;
}
