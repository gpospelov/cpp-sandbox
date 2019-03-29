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

class Item
{
public:
    Item(std::string model) : m_modelType(model), m_parent(nullptr) {
        std::cout << "Item() " << m_modelType << std::endl;
    }
    virtual ~Item() {
        std::cout << "~Item() " << m_modelType << std::endl;
        if (m_parent)
            m_parent->report_from_child(this);
    }

    void report_from_child(Item* child) {
        std::cout << "report_from_child() me: '" << m_modelType << "', child:'" << child->m_modelType << "'" << std::endl;
    }

    void setItem(Item* item) {
        std::cout << "setItem" << std::endl;
        item->setParent(this);
        m_child.reset(item);
    }

    void setParent(Item* parent)
    {
        std::cout << "setParent: me:'" << m_modelType << "', parent:'" << parent->m_modelType << "'" << std::endl;
        m_parent = parent;
    }
    std::unique_ptr<Item> m_child;
    std::string m_modelType;
    Item* m_parent;
};

class RootItem : public Item{
public:
    RootItem() : Item("root") {}
};

class Node : public Item{
public:
    Node() : Item("node") {}
};

int main()
{
//    std::cout << "--- before construction" << std::endl;
//    std::unique_ptr<Derived> d = std::make_unique<Derived>();
//    std::cout << "--- before destruction" << std::endl;
//    d.reset();
//    std::cout << "--- after destruction" << std::endl;

    auto root = new RootItem;
    auto node = new Node;
    root->setItem(node);
    delete root;
    return 0;
}
