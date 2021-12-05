#include "Borg/DependencyInjection/ServiceCollection.h"
#include <gtest/gtest.h>

using namespace Borg::DependencyInjection;

class IProduct
{
public:
    virtual ~IProduct() = default;
    virtual std::string Name() const = 0;
    virtual std::string Version() const = 0;
};

class Product : public IProduct
{
public:
    Product(const std::string &name) : m_Name(name) {}
    std::string Name() const override
    {
        return m_Name;
    }

    std::string Version() const override
    {
        return "1.0.0";
    }

private:
    std::string m_Name;
};

TEST(ServiceCollection, AddSingletonByInterface)
{
    ServiceCollection sc{};
    sc.AddSingleton<IProduct, Product>("File Explorer");

    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddSingletonByClass)
{
    ServiceCollection sc{};
    sc.AddSingleton<Product>("File Explorer");

    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
    auto product2 = serviceProvider->GetService<Product>();
    auto x = 0;
}
