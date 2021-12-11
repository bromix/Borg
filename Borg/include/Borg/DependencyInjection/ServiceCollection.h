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
         * @brief Adds a singleton service of the type specified in ServiceType with a callback to get an instance of the service.
         * 
         * @tparam ServiceType 
         * @param callback 
         */
        template <typename ServiceType>
        void AddSingleton(GetServiceWithProvider<ServiceType> &&callback);

        /**
         * @brief Adds a singleton service of the type specified in ServiceType with a callback to get an instance of the service.
         * 
         * @tparam ServiceType 
         * @param callback 
         */
        template <typename ServiceType>
        void AddSingleton(GetService<ServiceType> &&callback);

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
         * @brief Adds a transient service of the type specified in ServiceType with a callback to get an instance of the service.
         * 
         * @tparam ServiceType 
         * @param callback 
         */
        template <typename ServiceType>
        void AddTransient(GetServiceWithProvider<ServiceType> &&callback);

        /**
         * @brief Adds a transient service of the type specified in ServiceType with a callback to get an instance of the service.
         * 
         * @tparam ServiceType 
         * @param callback 
         */
        template <typename ServiceType>
        void AddTransient(GetService<ServiceType> &&callback);

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

        /**
         * @brief Adds a scoped service of the type specified in ServiceType with a callback to get an instance of the service.
         * 
         * @tparam ServiceType 
         * @param callback 
         */
        template <typename ServiceType>
        void AddScoped(GetServiceWithProvider<ServiceType> &&callback);

        /**
         * @brief Adds a scoped service of the type specified in ServiceType with a callback to get an instance of the service.
         * 
         * @tparam ServiceType 
         * @param callback 
         */
        template <typename ServiceType>
        void AddScoped(GetService<ServiceType> &&callback);

        /**
         * @brief Adds a scoped service of the type specified in ServiceType.
         *
         * @tparam ServiceType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType>
        void AddScoped();

        /**
         * @brief Adds a scoped service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType>
        void AddScoped();

    private:
        template <typename ServiceType>
        void AddByCallback(GetServiceWithProvider<ServiceType> &&callback, ServiceLifetime lifetime);

        template <typename ServiceType>
        void AddByCallback(GetService<ServiceType> &&callback, ServiceLifetime lifetime);

        template <typename ImplementationType>
        void AddByImplementationType(ServiceLifetime lifetime);

        template <typename ServiceType, typename ImplementationType>
        void AddByServiceTypeAndImplementationType(ServiceLifetime lifetime);

        ServiceMap m_Services;
    };

    Ref<ServiceProvider> ServiceCollection::BuildServiceProvider()
    {
        return CreateRef<ServiceProvider>(m_Services);
    }

    template <typename ServiceType>
    void ServiceCollection::AddByCallback(GetServiceWithProvider<ServiceType> &&callback, ServiceLifetime lifetime)
    {
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = TService<ServiceType>::CreateService<ServiceType>(std::move(callback), lifetime);
    }

    template <typename ServiceType>
    void ServiceCollection::AddByCallback(GetService<ServiceType> &&callback, ServiceLifetime lifetime)
    {
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = TService<ServiceType>::CreateService<ServiceType>(std::move(callback), lifetime);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddByImplementationType(ServiceLifetime lifetime)
    {
        auto hashCode = typeid(ImplementationType).hash_code();
        m_Services[hashCode] = TService<ImplementationType>::CreateService<ImplementationType>(lifetime);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddByServiceTypeAndImplementationType(ServiceLifetime lifetime)
    {
        auto hashCode = typeid(ServiceType).hash_code();
        m_Services[hashCode] = TService<ServiceType>::CreateService<ServiceType, ImplementationType>(lifetime);
    }

    template <typename ServiceType>
    void ServiceCollection::AddSingleton(GetServiceWithProvider<ServiceType> &&callback)
    {
        AddByCallback<ServiceType>(std::move(callback), ServiceLifetime::Singleton);
    }

    template <typename ServiceType>
    void ServiceCollection::AddSingleton(GetService<ServiceType> &&callback)
    {
        AddByCallback<ServiceType>(std::move(callback), ServiceLifetime::Singleton);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        AddByImplementationType<ImplementationType>(ServiceLifetime::Singleton);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        AddByServiceTypeAndImplementationType<ServiceType, ImplementationType>(ServiceLifetime::Singleton);
    }

    template <typename ServiceType>
    void ServiceCollection::AddTransient(GetServiceWithProvider<ServiceType> &&callback)
    {
        AddByCallback<ServiceType>(std::move(callback), ServiceLifetime::Transient);
    }

    template <typename ServiceType>
    void ServiceCollection::AddTransient(GetService<ServiceType> &&callback)
    {
        AddByCallback<ServiceType>(std::move(callback), ServiceLifetime::Transient);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddTransient()
    {
        AddByImplementationType<ImplementationType>(ServiceLifetime::Transient);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddTransient()
    {
        AddByServiceTypeAndImplementationType<ServiceType, ImplementationType>(ServiceLifetime::Transient);
    }

    template <typename ServiceType>
    void ServiceCollection::AddScoped(GetServiceWithProvider<ServiceType> &&callback)
    {
        AddByCallback<ServiceType>(std::move(callback), ServiceLifetime::Scoped);
    }

    template <typename ServiceType>
    void ServiceCollection::AddScoped(GetService<ServiceType> &&callback)
    {
        AddByCallback<ServiceType>(std::move(callback), ServiceLifetime::Scoped);
    }

    template <typename ImplementationType>
    void ServiceCollection::AddScoped()
    {
        AddByImplementationType<ImplementationType>(ServiceLifetime::Scoped);
    }

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddScoped()
    {
        AddByServiceTypeAndImplementationType<ServiceType, ImplementationType>(ServiceLifetime::Scoped);
    }
}