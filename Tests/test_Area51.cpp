#include "Borg/DependencyInjection/ServiceCollcetion.h"
#include <gtest/gtest.h>

using namespace Borg::DependencyInjection;

class IPerson
{
public:
    virtual ~IPerson() = default;
    virtual std::string Name() const = 0;
    virtual int Age() const = 0;
    virtual void SetName(const std::string &) = 0;
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

class Timer
{
public:
    int now() const
    {
        return 10;
    }
};

struct Product
{
    std::string Name = "";
    std::string Language = "en-US";
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

TEST(ServiceCollection, AddSingleton_Class)
{
    ServiceCollection sc{};
    sc.AddSingleton<Timer>();
    sc.AddSingleton<Product>();

    sc.GetService<Product>()->Name = "Burning Studio";

    auto timer = sc.GetService<Timer>();
    auto now = timer->now();

    sc.GetService<Product>()->Language = "de-DE";

    auto product = sc.GetService<Product>();
}