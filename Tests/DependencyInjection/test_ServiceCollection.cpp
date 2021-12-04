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

class Product: public IProduct
{
public:
    std::string Name() const override
    {
        return "File Explorer";
    }

    std::string Version() const override
    {
        return "1.0.0";
    }
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
