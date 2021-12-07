#pragma once
#include "Borg/Types.h"
#include "Service.h"
#include "ServiceProvider.h"
#include <typeindex>
#include <map>

// https://github.dev/aspnet/DependencyInjection/blob/master/src/DI/ServiceCollection.cs

namespace Borg::DependencyInjection
{
    template <typename ServiceType>
    using GetServiceCallback = Func<Ref<ServiceType>, const ServiceProvider&>;

    class ServiceCollection
    {
    public:
        /**
         * @brief Creates a ServiceProvider containing services from the provided ServiceCollection.
         *
         * @return Ref<ServiceProvider>
         */
        Ref<ServiceProvider> BuildServiceProvider();

        template <typename ServiceType>
        void AddSingleton(GetServiceCallback<ServiceType>&& callback);

        /**
         * @brief Adds a singleton service of the type specified in ServiceType
         *
         * @tparam ServiceType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType>
        void AddSingleton();

        /**
         * @brief Adds a singleton service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType>
        void AddSingleton();

        /**
         * @brief Adds a transient service of the type specified in ServiceType.
         *
         * @tparam ServiceType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType>
        void AddTransient();

        /**
         * @brief Adds a transient service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType>
        void AddTransient();

    private:
        ServiceMap m_Services;

        template <typename ServiceType, typename ImplementationType>
        ServiceConstructorFunc<ServiceType> createServiceFactory() const;
    };

    Ref<ServiceProvider> ServiceCollection::BuildServiceProvider()
    {
        return CreateRef<ServiceProvider>(m_Services);
    }

    template <typename ServiceType, typename ImplementationType>
    ServiceConstructorFunc<ServiceType> ServiceCollection::createServiceFactory() const
    {
        return [](const ServiceProvider&) -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>();
        };
    }

    template <typename ServiceType>
    void ServiceCollection::AddSingleton(GetServiceCallback<ServiceType>&& callback)
    {
        auto serviceConstructorFunc = [callback](const ServiceProvider& serviceProvider) -> Ref<ServiceType>
        {
            return callback(serviceProvider);
        };
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ServiceType>>(serviceConstructorFunc, ServiceLifetime::Singleton);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        IsClass<ImplementationType>();

        auto serviceConstructorFunc = createServiceFactory<ImplementationType, ImplementationType>();
        auto hashCode = typeid(ImplementationType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ImplementationType>>(serviceConstructorFunc, ServiceLifetime::Singleton);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        IsInterface<ServiceType>();
        Implements<ServiceType, ImplementationType>();
        IsClass<ImplementationType>();

        auto serviceConstructorFunc = createServiceFactory<ServiceType, ImplementationType>();
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ServiceType>>(serviceConstructorFunc, ServiceLifetime::Singleton);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddTransient()
    {
        IsClass<ImplementationType>();

        auto serviceConstructorFunc = createServiceFactory<ImplementationType, ImplementationType>();
        auto hashCode = typeid(ImplementationType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ImplementationType>>(serviceConstructorFunc, ServiceLifetime::Transient);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddTransient()
    {
        IsInterface<ServiceType>();
        Implements<ServiceType, ImplementationType>();
        IsClass<ImplementationType>();

        auto serviceConstructorFunc = createServiceFactory<ServiceType, ImplementationType>();
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ServiceType>>(serviceConstructorFunc, ServiceLifetime::Transient);
    }
}