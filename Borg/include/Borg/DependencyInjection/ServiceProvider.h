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

        auto serviceDescriptor = found->second;
        auto lifetime = serviceDescriptor->Lifetime();
        auto test = serviceDescriptor->Get<ServiceType>();

        Ref<TService<ServiceType>> service = std::static_pointer_cast<typename TService<ServiceType>>(found->second);
        return service->Get();
    }
}