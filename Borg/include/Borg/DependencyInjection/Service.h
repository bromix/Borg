#pragma once
#include <map>
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
    // Inspired by https://github.dev/william-taylor-projects/dil

    template <typename ServiceType>
    struct IsInterface
    {
        constexpr IsInterface()
        {
            static_assert(std::is_abstract<ServiceType>(), "ServiceType must be an interface/abstract class!");
        }
    };

    template <typename ServiceType, typename ImplementationType>
    struct Implements
    {
        constexpr Implements()
        {
            IsInterface<ServiceType>();
            static_assert(std::is_base_of<ServiceType, ImplementationType>(), "ServiceType doesnt implement ImplementationType");
        }
    };

    template <typename ImplementationType>
    struct IsClass
    {
        constexpr IsClass()
        {
            static_assert(std::is_class<ImplementationType>(), "ImplementationType must be a class");
        }
    };

    enum class ServiceLifetime
    {
        /**
         * @brief Specifies that a new instance of the service will be created for each scope. In ASP.NET Core apps, a scope is created around each server request.
         */
        Scoped = 1,

        /**
         * @brief Specifies that a single instance of the service will be created.
         */
        Singleton = 0,

        /**
         * @brief Specifies that a new instance of the service will be created every time it is requested.
         */
        Transient = 2
    };

    template <typename ServiceType>
    using ServiceFactory = Func<Ref<ServiceType>>;

    /**
     * @brief Base interface to be able to register the generic services based on their ServiceType.
     */
    class IService
    {
    public:
        using ServiceFactory = Func<Ref<void>>;

        IService(IService::ServiceFactory serviceFac, ServiceLifetime lifetime);
        ServiceLifetime Lifetime() const;

        template <typename ServiceType>
        Ref<ServiceType> Get();

    private:
        template <typename ServiceType>
        Ref<ServiceType> callServiceFactory();

        Func<Ref<void>> m_ServiceFactory;
        ServiceLifetime m_Lifetime = ServiceLifetime::Singleton;
    };

    /**
     * @brief Specialized service to hold the getter of the service.
     * @tparam T
     */
    template <typename ServiceType>
    struct TService : public IService
    {
    public:
        TService(ServiceFactory serviceFactory, ServiceLifetime lifetime)
            : IService(serviceFactory, lifetime)
        {
        }
    };

    /**
     * @brief Simplified definition of a map of serices.
     */
    using ServiceMap = std::map<std::size_t, Ref<IService>>;

    // ====================
    // ===== IService =====
    // ====================

    IService::IService(IService::ServiceFactory serviceFactory, ServiceLifetime lifetime)
        : m_Lifetime(lifetime),
          m_ServiceFactory(serviceFactory)
    {
    }

    ServiceLifetime IService::Lifetime() const
    {
        return m_Lifetime;
    }

    template <typename ServiceType>
    Ref<ServiceType> IService::callServiceFactory()
    {
        Ref<void> unknown = m_ServiceFactory();
        Ref<ServiceType> service = std::static_pointer_cast<typename ServiceType>(unknown);
        return service;
    }

    template <typename ServiceType>
    Ref<ServiceType> IService::Get()
    {
        if(m_Lifetime == ServiceLifetime::Singleton)
        {
            static Ref<ServiceType> instance = callServiceFactory<ServiceType>();
            return instance;
        }

        if(m_Lifetime == ServiceLifetime::Transient)
            return callServiceFactory<ServiceType>();

        // TODO: needs some kind of scope factory
        if(m_Lifetime == ServiceLifetime::Scoped)
            return callServiceFactory<ServiceType>();

        // FIXME: throw?
        return nullptr;
    }
}