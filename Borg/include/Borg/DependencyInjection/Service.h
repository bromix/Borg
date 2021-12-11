#pragma once
#include <map>
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
    class ServiceProvider;

    template <typename ServiceType>
    using GetServiceCallback = Func<Ref<ServiceType>, const ServiceProvider &>;

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

    /**
     * @brief Base interface to be able to register the generic services based on their ServiceType.
     */
    class IService
    {
    public:
        template <typename ServiceType>
        IService(GetServiceCallback<ServiceType> &&serviceConstructorFunc, ServiceLifetime lifetime)
            : m_GetServiceCallback(serviceConstructorFunc),
              m_Lifetime(lifetime)
        {
        }
        ServiceLifetime Lifetime() const;

        template <typename ServiceType>
        Ref<ServiceType> Get(const ServiceProvider &serviceProvider);

    private:
        template <typename ServiceType>
        Ref<ServiceType> getService(const ServiceProvider &serviceProvider);

        using IGetServiceCallback = Func<Ref<void>, const ServiceProvider &>;
        IService::IGetServiceCallback m_GetServiceCallback;
        ServiceLifetime m_Lifetime = ServiceLifetime::Singleton;
    };

    /**
     * @brief Specialized service to hold the getter of the service.
     * @tparam T
     */
    template <typename ServiceType>
    class TService : public IService
    {
    public:
        TService(GetServiceCallback<ServiceType> &&getServiceCallback, ServiceLifetime lifetime)
            : IService(std::move(getServiceCallback), lifetime)
        {
        }

        template <typename ServiceType, typename ImplementationType>
        static Ref<IService> CreateService(ServiceLifetime lifetime)
        {
            auto createService = [](const ServiceProvider &) -> Ref<ServiceType>
            {
                return CreateRef<ImplementationType>();
            };
            return CreateRef<TService<ServiceType>>(createService, lifetime);
        }

        template <typename ServiceType>
        static Ref<IService> CreateService(GetServiceCallback<ServiceType> &&callback, ServiceLifetime lifetime)
        {
            auto callServiceCallback = [callback](const ServiceProvider &serviceProvider) -> Ref<ServiceType>
            {
                return callback(serviceProvider);
            };
            return CreateRef<TService<ServiceType>>(std::move(callServiceCallback), lifetime);
        }
    };

    /**
     * @brief Simplified definition of a map of serices.
     */
    using ServiceMap = std::map<std::size_t, Ref<IService>>;

    // ====================
    // ===== IService =====
    // ====================

    ServiceLifetime IService::Lifetime() const
    {
        return m_Lifetime;
    }

    template <typename ServiceType>
    Ref<ServiceType> IService::getService(const ServiceProvider &serviceProvider)
    {
        return std::static_pointer_cast<ServiceType>(m_GetServiceCallback(serviceProvider));
    }

    template <typename ServiceType>
    Ref<ServiceType> IService::Get(const ServiceProvider &serviceProvider)
    {
        if (m_Lifetime == ServiceLifetime::Singleton)
        {
            static Ref<ServiceType> instance = getService<ServiceType>(serviceProvider);
            return instance;
        }

        if (m_Lifetime == ServiceLifetime::Transient)
            return getService<ServiceType>(serviceProvider);

        // TODO: needs some kind of scope factory
        if (m_Lifetime == ServiceLifetime::Scoped)
            return getService<ServiceType>(serviceProvider);

        // FIXME: throw?
        return nullptr;
    }
}