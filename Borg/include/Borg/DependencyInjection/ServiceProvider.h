#pragma once
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
    class ServiceProvider
    {
    public:
        ServiceProvider(const ServiceMap &serviceMap);

        template <typename ServiceType>
        Ref<ServiceType> GetService() const noexcept;

    private:
        ServiceMap m_Services;
    };

    ServiceProvider::ServiceProvider(const ServiceMap &serviceMap) : m_Services(serviceMap) {}

    template <typename ServiceType>
    Ref<ServiceType> ServiceProvider::GetService() const noexcept
    {
        auto hashCode = typeid(ServiceType).hash_code();
        auto found = m_Services.find(hashCode);
        if (found == m_Services.end())
            return nullptr;

        return found->second->Get<ServiceType>();
    }
}