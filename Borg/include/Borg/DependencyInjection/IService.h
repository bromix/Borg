#pragma once
#include <mutex>
#include "Service.h"

namespace Borg::DependencyInjection
{

    /**
     * @brief Base interface to be able to register the generic services based on their ServiceType.
     */
    class IService
    {
    public:
        friend ServiceProvider;

        template <typename ServiceType>
        IService(GetServiceWithProvider<ServiceType> &&getServiceImplemenationFunc, ServiceLifetime lifetime)
            : m_GetServiceImplemenationFunc(getServiceImplemenationFunc),
              m_Lifetime(lifetime)
        {
        }

        ~IService()
        {
        }

        inline ServiceLifetime Lifetime() const;

    private:
        /**
         * @brief Used by the ServiceProvider to get the serivce.
         *
         * @tparam ServiceType
         * @param serviceProvider
         * @return Ref<ServiceType>
         */
        template <typename ServiceType>
        Ref<ServiceType> Get(const ServiceProvider &serviceProvider);

        /**
         * @brief Internal helper function to get the service.
         *
         * @tparam ServiceType
         * @param serviceProvider
         * @return Ref<ServiceType>
         */
        template <typename ServiceType>
        Ref<ServiceType> getServiceImplementation(const ServiceProvider &serviceProvider);

        /**
         * @brief Internal callback to cast down to void*
         */
        using IGetServiceCallback = Func<Ref<void>, const ServiceProvider &>;

        /**
         * @brief Specialized function/callback to get the service.
         */
        IService::IGetServiceCallback m_GetServiceImplemenationFunc;

        /**
         * @brief The lifetime of this service.
         */
        ServiceLifetime m_Lifetime = ServiceLifetime::Singleton;

        /**
         * @brief Used for singleton services.
         */
        Ref<void> m_ServiceInstance = nullptr;

        std::mutex m_SingletonMutex;
    };

    ServiceLifetime IService::Lifetime() const
    {
        return m_Lifetime;
    }

    template <typename ServiceType>
    Ref<ServiceType> IService::getServiceImplementation(const ServiceProvider &serviceProvider)
    {
        return RefCast<ServiceType>(m_GetServiceImplemenationFunc(serviceProvider));
    }

    template <typename ServiceType>
    Ref<ServiceType> IService::Get(const ServiceProvider &serviceProvider)
    {
        if (m_Lifetime == ServiceLifetime::Singleton)
        {
            {
                // Scope mutex only to this section
                std::lock_guard<std::mutex> lockSingleton(m_SingletonMutex);
                if (!m_ServiceInstance)
                    m_ServiceInstance = getServiceImplementation<ServiceType>(serviceProvider);

                return RefCast<ServiceType>(m_ServiceInstance);
            }
        }

        if (m_Lifetime == ServiceLifetime::Transient)
            return getServiceImplementation<ServiceType>(serviceProvider);

        // TODO: needs some kind of scope factory
        if (m_Lifetime == ServiceLifetime::Scoped)
            return getServiceImplementation<ServiceType>(serviceProvider);

        // FIXME: throw?
        return nullptr;
    }
}