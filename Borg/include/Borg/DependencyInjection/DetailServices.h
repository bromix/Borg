#pragma once
#include "Borg/Types.h"

namespace Borg::DependencyInjection::Detail
{
    class Services
    {
    public:
        using ConfigureType = Action<ServiceCollection &>;

        Services(Services::ConfigureType configure)
            : m_Configure(configure)
        {
        }

        template <typename ServiceType>
        Ref<ServiceType> GetService()
        {
            std::lock_guard<std::mutex> lock(m_GetServiceLock);

            if (!m_ServiceProvider)
            {
                m_Configure(*m_ServiceCollection.get());
                m_ServiceProvider = m_ServiceCollection->BuildServiceProvider();
            }

            return m_ServiceProvider->GetService<ServiceType>();
        }

    private:
        std::mutex m_GetServiceLock;
        Ref<ServiceCollection> m_ServiceCollection = CreateRef<ServiceCollection>();
        Ref<ServiceProvider> m_ServiceProvider;
        Services::ConfigureType m_Configure;
    };
}