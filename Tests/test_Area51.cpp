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
    std::string Name() const { return "Hans"; };
    virtual int Age() const { return 34; };
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
    sc.AddSingleton<IPerson, PersonImpl>();

    auto p = sc.GetService<IPerson>();
    auto name = p->Name();

    auto p2 = sc.GetService<IPerson>();
    auto name2 = p2->Name();
}