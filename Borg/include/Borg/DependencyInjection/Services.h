#pragma once
#include <optional>
#include "Borg/Types.h"
#include "ServiceCollection.h"
#include "DetailServices.h"

namespace Borg::DependencyInjection
{
    class Services final
    {
    public:
        using ConfigureType = Detail::Services::ConfigureType;

        Services() = delete;

        static void Configure(Services::ConfigureType configure)
        {
            std::lock_guard<std::mutex> lock(m_ServicesLock);

            if (m_Services)
                throw InvalidOperationException("Services::Configure can only be called once.");

            m_Services = CreateRef<Detail::Services>(configure);
        }

        template <typename ServiceType>
        static Ref<ServiceType> GetService()
        {
            std::lock_guard<std::mutex> lock(m_ServicesLock);

            if (!m_Services)
                throw InvalidOperationException("Service::Configure was not called");

            return m_Services->GetService<ServiceType>();
        }

    private:
        static std::mutex m_ServicesLock;
        static Ref<Detail::Services> m_Services;
    };
}