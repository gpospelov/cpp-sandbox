/*
Polymorphic clone with covariance for modern smart pointer way.
Following https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance
*/
#include <iostream>
#include <memory>

namespace Simple
{

class Cloneable
{
public:
    virtual ~Cloneable();

    std::unique_ptr<Cloneable> clone() const
    {
        return std::unique_ptr<Cloneable>(this->clone_impl());
    }

private:
    virtual Cloneable* clone_impl() const = 0;
};

Cloneable::~Cloneable() = default;

class Concrete : public Cloneable
{
public:
    ~Concrete() override;

    // hiding original method
    std::unique_ptr<Concrete> clone() const
    {
        return std::unique_ptr<Concrete>(this->clone_impl());
    }

private:
    Concrete* clone_impl() const override { return new Concrete(*this); }
};

Concrete::~Concrete() = default;

} // namespace Simple

// ----------------------------------------------------------------------------

namespace CRTP
{

class Cloneable
{
public:
    virtual ~Cloneable();

    std::unique_ptr<Cloneable> clone() const
    {
        return std::unique_ptr<Cloneable>(this->clone_impl());
    }

private:
    virtual Cloneable* clone_impl() const = 0;
};

Cloneable::~Cloneable() = default;

template <typename Derived, typename Base> class CloneInherit : public Base
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

class Concrete : public CloneInherit<Concrete, Cloneable>
{
};

} // namespace CRTP

// ----------------------------------------------------------------------------

int main()
{
    std::cout << "Hello world" << std::endl;

    // Clone using simple method hiding
    std::unique_ptr<Simple::Concrete> c = std::make_unique<Simple::Concrete>();
    std::unique_ptr<Simple::Concrete> cc = c->clone();

    Simple::Cloneable* p = c.get();
    std::unique_ptr<Simple::Cloneable> pp = p->clone();

    // Clone using curiously reccuring template pattern
    std::unique_ptr<CRTP::Concrete> c2 = std::make_unique<CRTP::Concrete>();
    std::unique_ptr<CRTP::Concrete> cc2 = c2->clone();

    CRTP::Cloneable* p2 = c2.get();
    std::unique_ptr<CRTP::Cloneable> pp2 = p2->clone();
}
