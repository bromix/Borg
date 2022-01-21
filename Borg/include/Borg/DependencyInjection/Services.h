#pragma once
#include <optional>
#include "Borg/Types.h"
#include "ServiceCollection.h"

namespace Borg::DependencyInjection
{
    class Services final
    {
    public:
        using ConfigureType = Action<ServiceCollection &>;
        Services() = delete;
        static void Configure(Services::ConfigureType configure);

        template <typename ServiceType>
        static Ref<ServiceType> GetService() noexcept
        {
            if(!g_ServiceProvider)
            {
                g_Configure(*g_ServiceCollection.get());
                g_ServiceProvider = g_ServiceCollection->BuildServiceProvider();
            }
            return g_ServiceProvider->GetService<ServiceType>();
        }
    private:
        static Ref<ServiceCollection> g_ServiceCollection;
        static Services::ConfigureType g_Configure;
        static Ref<ServiceProvider> g_ServiceProvider;
    };
}