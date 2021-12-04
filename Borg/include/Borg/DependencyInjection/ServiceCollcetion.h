#pragma once
#include "Borg/Types.h"
#include <typeindex>
#include <map>

namespace Borg::DependencyInjection
{
    class ServiceCollection
    {
    public:
        /**
         * @brief Adds a singleton service of the type specified in serviceType
         *
         * @tparam ServiceType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename... Args>
        void AddSingleton(Args &&...args);

        /**
         * @brief Adds a singleton service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType, typename... Args>
        void AddSingleton(Args &&...args);

        /**
         * @brief Adds a transient service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType, typename... Args>
        void AddTransient(Args &&...args);

        // FIXME: move to ServiceProvider
        template <typename ServiceType>
        Ref<ServiceType> GetService();

    private:
        template <typename ServiceType>
        using ServiceGetterFunc = Func<Ref<ServiceType>>;

        /**
         * @brief Base interface to be able to register the generic services based on their ServiceType.
         */
        class IService
        {
        };

        /**
         * @brief Specialized service to hold the getter of the service.
         * @tparam T
         */
        template <typename ServiceType>
        struct TService : public IService
        {
        public:
            TService(ServiceGetterFunc<ServiceType> serviceGetter) : Get(std::move(serviceGetter)) {}
            const ServiceGetterFunc<ServiceType> Get;
        };

        // FIXME: use hashcode.
        std::map<std::type_index, Ref<IService>> m_Services;

        template <typename ServiceType, typename ImplementationType, typename... Args>
        ServiceGetterFunc<ServiceType> createServiceGetterForSingleton(Args &&...args);
    };

    template <typename ServiceType, typename ImplementationType, typename... Args>
    ServiceCollection::ServiceGetterFunc<ServiceType> ServiceCollection::createServiceGetterForSingleton(Args &&...args)
    {
        return [args...]() -> Ref<ServiceType>
        {
            static Ref<ServiceType> service = CreateRef<ImplementationType>(std::forward<Args>(args)...);
            return service;
        };
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddSingleton(Args &&...args)
    {
        static_assert(std::is_abstract<ServiceType>(), "First type must be an interface or abstract class.");
        static_assert(std::is_base_of<ServiceType, ImplementationType>(), "Second type must implement first type.");
        static_assert(std::is_class<ImplementationType>(), "Second type must be a class");

        auto tyin1 = std::type_index(typeid(ServiceType));

        auto tyhash1 = tyin1.hash_code();

        auto serviceGetter = createServiceGetterForSingleton<ServiceType, ImplementationType, Args...>(std::forward<Args>(args)...);

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(serviceGetter);
    }

    template <typename ServiceType, typename... Args>
    void ServiceCollection::AddSingleton(Args &&...args)
    {
        static_assert(std::is_class<ServiceType>(), "Second type must be a class");

        auto tyin1 = std::type_index(typeid(ServiceType));

        auto tyhash1 = tyin1.hash_code();

        auto serviceGetter = createServiceGetterForSingleton<ServiceType, ServiceType, Args...>(std::forward<Args>(args)...);

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(serviceGetter);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddTransient(Args &&...args)
    {
        static_assert(std::is_abstract<ServiceType>(), "First type must be an interface or abstract class.");
        static_assert(std::is_base_of<ServiceType, ImplementationType>(), "Second type must implement first type.");
        static_assert(std::is_class<ImplementationType>(), "Second type must be a class");

        auto tyin1 = std::type_index(typeid(ServiceType));
        auto tyin2 = std::type_index(typeid(ImplementationType));

        auto tyhash1 = tyin1.hash_code();
        auto tyhash2 = tyin2.hash_code();

        ServiceGetterFunc<ServiceType> serviceGetter = [args...]() -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>(std::forward<Args>(args)...);
        };

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(serviceGetter);
    }

    template <typename ServiceType>
    Ref<ServiceType> ServiceCollection::GetService()
    {
        auto tyin1 = std::type_index(typeid(ServiceType));
        auto found = m_Services.find(tyin1);
        if (found == m_Services.end())
            return nullptr;

        Ref<TService<ServiceType>> tService = std::static_pointer_cast<typename TService<ServiceType>>(found->second);
        return tService->Get();
    }
}