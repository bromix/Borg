#include "Borg/DependencyInjection/Services.h"
#include "Borg/DependencyInjection/ServiceCollection.h"
#include "Borg/Exception.h"

namespace Borg::DependencyInjection
{
    Ref<ServiceCollection> Services::g_ServiceCollection;
    Services::ConfigureType Services::g_Configure;
    Ref<ServiceProvider> Services::g_ServiceProvider;

    void Services::Configure(Services::ConfigureType configure)
    {
        if (g_ServiceCollection || g_Configure)
            throw InvalidOperationException("Services::Configure can only be called once.");

        g_ServiceCollection = CreateRef<ServiceCollection>();
        g_Configure = configure;
    }
}