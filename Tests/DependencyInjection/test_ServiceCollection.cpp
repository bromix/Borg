#include "Borg/DependencyInjection/ServiceCollection.h"
#include <gtest/gtest.h>

using namespace Borg::DependencyInjection;

class IUser
{
public:
    virtual ~IUser() = default;
};

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
    Product(const std::string &name = "File Explorer") : m_Name(name) {}
    ~Product()
    {
    }
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
    sc.AddSingleton<IProduct, Product>();

    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddSingletonByInterface2)
{
    ServiceCollection sc{};
    sc.AddSingleton<IProduct>([](const ServiceProvider &sp) -> Borg::Ref<IProduct>
                              {
                                  auto user = sp.GetService<IUser>();
                                  return Borg::CreateRef<Product>("File Explorer"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddSingletonByClass)
{
    ServiceCollection sc{};
    sc.AddSingleton<Product>([](const ServiceProvider &sp) -> Borg::Ref<Product> {
        return Borg::CreateRef<Product>("File Explorer");
    });

    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
    auto product2 = serviceProvider->GetService<Product>();
    auto x = 0;
}
