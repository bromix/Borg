#include "Borg/ServiceCollcetion.h"
#include <gtest/gtest.h>

using namespace Borg;

class IPerson
{
public:
    virtual ~IPerson() = default;
    virtual std::string Name() const = 0;
    virtual int Age() const = 0;
};

class PersonImpl : public IPerson
{
public:
    PersonImpl() : PersonImpl("Hans") {}
    PersonImpl(const std::string &name) : m_Name(name) {}
    std::string Name() const { return m_Name; };
    virtual int Age() const { return 34; };

private:
    std::string m_Name;
};

class IAnimal
{
public:
    virtual ~IAnimal() = default;
    virtual std::string Name() const = 0;
};

TEST(Area51, ServiceCollection)
{
    ServiceCollection sc{};
    sc.AddSingleton<IPerson, PersonImpl>("Peter");

    auto p = sc.GetService<IPerson>();
    auto name = p->Name();

    auto p2 = sc.GetService<IPerson>();
    auto name2 = p2->Name();
}