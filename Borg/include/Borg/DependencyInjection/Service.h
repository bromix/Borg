#pragma once
#include <map>
#include "Borg/Types.h"

namespace Borg::DependencyInjection
{
    class ServiceProvider;

    template <typename ServiceType>
    using GetServiceWithProvider = Func<Ref<ServiceType>, const ServiceProvider &>;

    template <typename ServiceType>
    using GetService = Func<Ref<ServiceType>>;

    // Inspired by https://github.dev/william-taylor-projects/dil

    template <typename ServiceType>
    struct IsInterface
    {
        constexpr IsInterface()
        {
            static_assert(std::is_abstract<ServiceType>(), "ServiceType must be an interface/abstract class!");
        }
    };

    template <typename ServiceType, typename ImplementationType>
    struct Implements
    {
        constexpr Implements()
        {
            IsInterface<ServiceType>();
            static_assert(std::is_base_of<ServiceType, ImplementationType>(), "ServiceType doesnt implement ImplementationType");
        }
    };

    template <typename ImplementationType>
    struct IsClass
    {
        constexpr IsClass()
        {
            static_assert(std::is_class<ImplementationType>(), "ImplementationType must be a class");
        }
    };

    enum class ServiceLifetime
    {
        /**
         * @brief Specifies that a new instance of the service will be created for each scope. In ASP.NET Core apps, a scope is created around each server request.
         */
        Scoped = 1,

        /**
         * @brief Specifies that a single instance of the service will be created.
         */
        Singleton = 0,

        /**
         * @brief Specifies that a new instance of the service will be created every time it is requested.
         */
        Transient = 2
    };

    

    /**
     * @brief Simplified definition of a map of serices.
     */
    class IService;
    using ServiceMap = std::map<std::size_t, Ref<IService>>;
}