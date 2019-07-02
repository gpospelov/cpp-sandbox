// Polymorphic clone with covariance for modern smart pointer way.
// Following https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance
#include <iostream>
#include <memory>

namespace Simple {

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

} // namespace simple

int main()
{
    std::cout << "Hello world" << std::endl;

    std::unique_ptr<Simple::Concrete> c = std::make_unique<Simple::Concrete>();
    std::unique_ptr<Simple::Concrete> cc = c->clone();

    Simple::Cloneable* p = c.get();
    std::unique_ptr<Simple::Cloneable> pp = p->clone();
}
