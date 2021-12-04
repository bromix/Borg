#include "Borg/DependencyInjection/ServiceCollcetion.h"
#include <gtest/gtest.h>

using namespace Borg::DependencyInjection;

class IPerson
{
public:
    virtual ~IPerson() = default;
    virtual std::string Name() const = 0;
    virtual int Age() const = 0;
    virtual void SetName(const std::string&) = 0;
};

class PersonImpl : public IPerson
{
public:
    PersonImpl() : PersonImpl("Hans") {}
    PersonImpl(const std::string &name) : m_Name(name) {}
    std::string Name() const { return m_Name; };
    void SetName(const std::string &name) { m_Name = name; };
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

class ICounter
{
public:
    virtual ~ICounter() = default;
    virtual int count() = 0;
};

class CounterImpl : public ICounter
{
public:
    int count() override
    {
        return ++m_Counter;
    }

private:
    int m_Counter = 0;
};

TEST(Area51, ServiceCollection)
{
    ServiceCollection sc{};
    sc.AddSingleton<IPerson, PersonImpl>("Peter");
    sc.AddTransient<ICounter, CounterImpl>();

    auto p = sc.GetService<IPerson>();
    auto name = p->Name();
    p->SetName("Thomas");

    auto pX = sc.GetService<IPerson>();
    auto nameX = pX->Name();

    auto p2 = sc.GetService<ICounter>();
    auto c2 = p2->count();

    auto p3 = sc.GetService<ICounter>();
    auto c3 = p3->count();
}