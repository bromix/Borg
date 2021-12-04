#pragma once
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
    class ServiceProvider
    {
    public:
        template <typename ServiceType>
        Ref<ServiceType> GetService() const noexcept;
    };

    template <typename ServiceType>
    Ref<ServiceType> ServiceProvider::GetService() const noexcept
    {
        return nullptr;
    }
}