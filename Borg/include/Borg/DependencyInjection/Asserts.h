#pragma once
namespace Borg::DependencyInjection
{
    // Inspired by https://github.dev/william-taylor-projects/dil

    template <typename ServiceType>
    struct IsInterface
    {
        constexpr IsInterface()
        {
            static_assert(std::is_abstract<ServiceType>(), "ServiceType must be an interface/abstract class!");
        }
    };

    template <typename Interface, typename Implementee>
    struct Implements
    {
        constexpr Implements()
        {
            IsInterface<Interface>();
            static_assert(std::is_base_of<Interface, Implementee>(), "Implementee doesnt implement Interface");
        }
    };

    template <typename Object>
    struct IsClass
    {
        constexpr IsClass()
        {
            static_assert(std::is_class<Object>(), "Object must be a class");
        }
    };
}