#pragma once
#include "Service.h"
#include "IService.h"

namespace Borg::DependencyInjection
{
    class ServiceProvider
    {
    public:
        ServiceProvider(const ServiceMap &serviceMap);
        ~ServiceProvider();

        template <typename ServiceType>
        Ref<ServiceType> GetService() const noexcept;

    private:
        ServiceMap m_Services;
    };

    ServiceProvider::ServiceProvider(const ServiceMap &serviceMap) : m_Services(serviceMap) {}

    ServiceProvider::~ServiceProvider()
    {
        for (auto service : m_Services)
        {
            if (service.second->Lifetime() == ServiceLifetime::Singleton)
            {
            }
        }
    }

    template <typename ServiceType>
    Ref<ServiceType> ServiceProvider::GetService() const noexcept
    {
        auto hashCode = typeid(ServiceType).hash_code();
        auto found = m_Services.find(hashCode);
        if (found == m_Services.end())
            return nullptr;

        return found->second->Get<ServiceType>(*this);
    }
}