#pragma once
#include <map>
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
    /**
     * @brief Base interface to be able to register the generic services based on their ServiceType.
     */
    class IService
    {
    public:
        template <typename ServiceType>
        using GetterFunc = Func<Ref<ServiceType>>;
    };

    /**
     * @brief Specialized service to hold the getter of the service.
     * @tparam T
     */
    template <typename ServiceType>
    struct TService : public IService
    {
    public:
        TService(GetterFunc<ServiceType> serviceGetter) : Get(std::move(serviceGetter)) {}
        const GetterFunc<ServiceType> Get;
    };

    using ServiceMap = std::map<std::size_t, Ref<IService>>;
}