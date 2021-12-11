#pragma once
#include "Borg/Types.h"
#include "Service.h"
#include "ServiceProvider.h"
#include <typeindex>
#include <map>

// https://github.dev/aspnet/DependencyInjection/blob/master/src/DI/ServiceCollection.cs

namespace Borg::DependencyInjection
{
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
        void AddSingleton(GetServiceCallback<ServiceType> &&callback);

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
    };

    Ref<ServiceProvider> ServiceCollection::BuildServiceProvider()
    {
        return CreateRef<ServiceProvider>(m_Services);
    }

    template <typename ServiceType>
    void ServiceCollection::AddSingleton(GetServiceCallback<ServiceType> &&callback)
    {
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = TService<ServiceType>::CreateService<ServiceType>(std::move(callback), ServiceLifetime::Singleton);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        IsClass<ImplementationType>();

        auto hashCode = typeid(ImplementationType).hash_code();
        m_Services[hashCode] = TService<ImplementationType>::CreateService<ImplementationType, ImplementationType>(ServiceLifetime::Singleton);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        IsInterface<ServiceType>();
        Implements<ServiceType, ImplementationType>();
        IsClass<ImplementationType>();

        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = TService<ServiceType>::CreateService<ServiceType, ImplementationType>(ServiceLifetime::Singleton);
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