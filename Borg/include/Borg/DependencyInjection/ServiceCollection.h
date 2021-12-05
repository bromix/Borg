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

        /**
         * @brief Adds a singleton service of the type specified in ServiceType
         *
         * @tparam ServiceType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename... Args>
        void AddSingleton(Args &&...args);

        /**
         * @brief Adds a singleton service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType, typename... Args>
        void AddSingleton(Args &&...args);

        /**
         * @brief Adds a transient service of the type specified in ServiceType.
         *
         * @tparam ServiceType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename... Args>
        void AddTransient(Args &&...args);

        /**
         * @brief Adds a transient service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType, typename... Args>
        void AddTransient(Args &&...args);

    private:
        ServiceMap m_Services;

        template <typename ServiceType, typename ImplementationType, typename... Args>
        IService::GetterFunc<ServiceType> createServiceGetterForSingleton(Args &&...args);

        template <typename ServiceType, typename ImplementationType, typename... Args>
        IService::GetterFunc<ServiceType> createServiceGetterForTransient(Args &&...args);
    };

    Ref<ServiceProvider> ServiceCollection::BuildServiceProvider()
    {
        return CreateRef<ServiceProvider>(m_Services);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    IService::GetterFunc<ServiceType> ServiceCollection::createServiceGetterForSingleton(Args &&...args)
    {
        return [args...]() -> Ref<ServiceType>
        {
            static Ref<ServiceType> service = CreateRef<ImplementationType>(std::forward<Args>(args)...);
            return service;
        };
    }

    template <typename ImplementationType, typename... Args>
    void ServiceCollection::AddSingleton(Args &&...args)
    {
        IsClass<ImplementationType>();

        auto serviceGetter = createServiceGetterForSingleton<ImplementationType, ImplementationType, Args...>(std::forward<Args>(args)...);
        auto hashCode = typeid(ImplementationType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ImplementationType>>(serviceGetter, ServiceLifetime::Singleton);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddSingleton(Args &&...args)
    {
        IsInterface<ServiceType>();
        Implements<ServiceType, ImplementationType>();
        IsClass<ImplementationType>();

        auto serviceGetter = createServiceGetterForSingleton<ServiceType, ImplementationType, Args...>(std::forward<Args>(args)...);
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ServiceType>>(serviceGetter, ServiceLifetime::Singleton);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    IService::GetterFunc<ServiceType> ServiceCollection::createServiceGetterForTransient(Args &&...args)
    {
        return [args...]() -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>(std::forward<Args>(args)...);
        };
    }

    template <typename ImplementationType, typename... Args>
    void ServiceCollection::AddTransient(Args &&...args)
    {
        IsClass<ImplementationType>();

        auto serviceGetter = createServiceGetterForTransient<ImplementationType, ImplementationType, Args...>(std::forward<Args>(args)...);
        auto hashCode = typeid(ImplementationType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ImplementationType>>(serviceGetter, ServiceLifetime::Transient);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddTransient(Args &&...args)
    {
        IsInterface<ServiceType>();
        Implements<ServiceType, ImplementationType>();
        IsClass<ImplementationType>();

        auto serviceGetter = createServiceGetterForTransient<ServiceType, ImplementationType, Args...>(std::forward<Args>(args)...);
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = CreateRef<TService<ServiceType>>(serviceGetter, ServiceLifetime::Transient);
    }
}