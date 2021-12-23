#include "Borg/DependencyInjection/ServiceProvider.h"
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
    virtual void SetVersion(const std::string &) = 0;
};

class Product : public IProduct
{
public:
    Product(const std::string &name = "File Explorer", const std::string& version = "1.0.0")
        : m_Name(name),
          m_Version(version)
    {
    }

    ~Product()
    {
    }
    std::string Name() const override
    {
        return m_Name;
    }

    std::string Version() const override
    {
        return m_Version;
    }

    virtual void SetVersion(const std::string &version)
    {
        m_Version = version;
    }

private:
    std::string m_Version;
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

    product->SetVersion("2.0.0");

    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("2.0.0", product->Version());
}

TEST(ServiceCollection, AddSingletonInterfaceByCallbackWithServiceProvider)
{
    ServiceCollection sc{};
    sc.AddSingleton<IProduct>([](const ServiceProvider &sp) -> Borg::Ref<IProduct>
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("2.0.0", product->Version());
}

TEST(ServiceCollection, AddSingletonInterfaceByCallback)
{
    ServiceCollection sc{};
    sc.AddSingleton<IProduct>([]() -> Borg::Ref<IProduct>
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("2.0.0", product->Version());
}

TEST(ServiceCollection, AddSingletonByClass)
{
    ServiceCollection sc{};
    sc.AddSingleton<Product>([](const ServiceProvider &sp) -> Borg::Ref<Product>
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("2.0.0", product->Version());
}

TEST(ServiceCollection, AddTransientByInterface)
{
    ServiceCollection sc{};
    sc.AddTransient<IProduct, Product>();

    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");

    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddTransientInterfaceByCallback)
{
    ServiceCollection sc{};
    sc.AddTransient<IProduct>([](const ServiceProvider &sp) -> Borg::Ref<IProduct>
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddTransientByClass)
{
    ServiceCollection sc{};
    sc.AddTransient<Product>([](const ServiceProvider &sp) -> Borg::Ref<Product>
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddScopedByInterface)
{
    ServiceCollection sc{};
    sc.AddScoped<IProduct, Product>();

    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");

    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddScopedInterfaceByCallback)
{
    ServiceCollection sc{};
    sc.AddScoped<IProduct>([](const ServiceProvider &sp)
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<IProduct>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}

TEST(ServiceCollection, AddScopedByClass)
{
    ServiceCollection sc{};
    sc.AddScoped<Product>([](const ServiceProvider &sp) -> Borg::Ref<Product>
                              { return Borg::CreateRef<Product>("File Explorer", "1.0.0"); });
    auto serviceProvider = sc.BuildServiceProvider();
    auto product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());

    product->SetVersion("2.0.0");
    product = serviceProvider->GetService<Product>();
    ASSERT_EQ("File Explorer", product->Name());
    ASSERT_EQ("1.0.0", product->Version());
}