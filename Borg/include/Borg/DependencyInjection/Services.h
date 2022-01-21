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
            if (m_Services)
                throw InvalidOperationException("Services::Configure can only be called once.");

            m_Services = CreateRef<Detail::Services>(configure);
        }

        template <typename ServiceType>
        static Ref<ServiceType> GetService()
        {
            if(!m_Services)
                throw InvalidOperationException("Service::Configure was not called");

            return m_Services->GetService<ServiceType>();
        }

    private:
        static Ref<Detail::Services> m_Services;
    };

    Ref<Detail::Services> Services::m_Services;
}