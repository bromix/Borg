#pragma once
#include <map>
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
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
        using GetterFunc = Func<Ref<ServiceType>>;

        IService(ServiceLifetime lifetime);
        ServiceLifetime Lifetime() const;

    private:
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
        TService(GetterFunc<ServiceType> serviceGetter, ServiceLifetime lifetime)
            : IService(lifetime),
              Get(std::move(serviceGetter))
        {
        }

        const GetterFunc<ServiceType> Get;
    };

    /**
     * @brief Simplified definition of a map of serices.
     */
    using ServiceMap = std::map<std::size_t, Ref<IService>>;

    // ====================
    // ===== IService =====
    // ====================

    IService::IService(ServiceLifetime lifetime)
        : m_Lifetime(lifetime)
    {
    }

    ServiceLifetime IService::Lifetime() const
    {
        return m_Lifetime;
    }
}