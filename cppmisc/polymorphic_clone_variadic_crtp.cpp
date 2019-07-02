/*
Polymorphic clone with covariance using CRTP pattern and variadic inheritance.
Following https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance
*/
#include <iostream>
#include <memory>

template <typename Derived, typename... Bases> class CloneInherit : public Bases...
{
public:
    std::unique_ptr<Derived> clone() const
    {
        return std::unique_ptr<Derived>(static_cast<Derived*>(this->clone_impl()));
    }

private:
    virtual CloneInherit* clone_impl() const override
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

template <typename Derived> class CloneInherit<Derived>
{
public:
    virtual ~CloneInherit() = default;

    std::unique_ptr<Derived> clone() const
    {
        return std::unique_ptr<Derived>(static_cast<Derived*>(this->clone_impl()));
    }

private:
    virtual CloneInherit* clone_impl() const = 0;
};

class Foo : public CloneInherit<Foo>
{
};

class Bar : public CloneInherit<Bar>
{
};

class Concrete : public CloneInherit<Concrete, Foo, Bar>
{
};

// ----------------------------------------------------------------------------

int main()
{
    std::cout << "Hello world" << std::endl;

    std::unique_ptr<Concrete> c = std::make_unique<Concrete>();

    std::unique_ptr<Concrete> cc = c->clone();

    Foo* f = c.get();
    std::unique_ptr<Foo> ff = f->clone();

    Bar* b = c.get();
    std::unique_ptr<Bar> bb = b->clone();
}
