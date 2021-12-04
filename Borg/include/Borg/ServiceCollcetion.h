#include <typeindex>
#include <map>
#include "Types.h"

namespace Borg
{
    template <typename ServiceType>
    using ServiceGetterFunc = Func<Ref<ServiceType>>;

    /**
     * @brief Base interface to derive each generic service type from.
     */
    class IServiceProvider
    {
    };

    template <typename T>
    struct TServiceProvider : public IServiceProvider
    {
    public:
        TServiceProvider(ServiceGetterFunc<T> serviceGetter) : Get(std::move(serviceGetter)) {}
        const ServiceGetterFunc<T> Get;
    };

    class ServiceCollection
    {
    public:
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
         * @brief Adds a scoped service of the type specified in ServiceType with an implementation of the type specified in ImplementationType.
         *
         * @tparam ServiceType
         * @tparam ImplementationType
         * @tparam Args
         * @param args
         */
        template <typename ServiceType, typename ImplementationType, typename... Args>
        void AddScoped(Args &&...args);

        // FIXME: move to ServiceProvider
        template <typename ServiceType>
        Ref<ServiceType> GetService();

    private:
        // FIXME: use hashcode.
        std::map<std::type_index, Ref<IServiceProvider>> m_ServiceProvider;
    };

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddSingleton(Args &&...args)
    {
        static_assert(std::is_abstract<ServiceType>(), "First type must be an interface or abstract class.");
        static_assert(std::is_base_of<ServiceType, ImplementationType>(), "Second type must implement first type.");
        static_assert(std::is_class<ImplementationType>(), "Second type must be a class");

        auto tyin1 = std::type_index(typeid(ServiceType));
        auto tyin2 = std::type_index(typeid(ImplementationType));

        auto tyhash1 = tyin1.hash_code();
        auto tyhash2 = tyin2.hash_code();

        ServiceGetterFunc<ServiceType> singletonGetter = [=]() -> Ref<ServiceType>
        {
            static Ref<ServiceType> _service = CreateRef<ImplementationType>(std::forward<Args>(args)...);
            return _service;
        };

        m_ServiceProvider[tyin1] = CreateRef<TServiceProvider<ServiceType>>(singletonGetter);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddScoped(Args &&...args)
    {
        static_assert(std::is_abstract<ServiceType>(), "First type must be an interface or abstract class.");
        static_assert(std::is_base_of<ServiceType, ImplementationType>(), "Second type must implement first type.");
        static_assert(std::is_class<ImplementationType>(), "Second type must be a class");

        auto tyin1 = std::type_index(typeid(ServiceType));
        auto tyin2 = std::type_index(typeid(ImplementationType));

        auto tyhash1 = tyin1.hash_code();
        auto tyhash2 = tyin2.hash_code();

        ServiceGetterFunc<ServiceType> scopedGetter = [=]() -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>(std::forward<Args>(args)...);
        };

        m_ServiceProvider[tyin1] = CreateRef<TServiceProvider<ServiceType>>(scopedGetter);
    }

    template <typename ServiceType>
    Ref<ServiceType> ServiceCollection::GetService()
    {
        auto tyin1 = std::type_index(typeid(ServiceType));
        auto found = m_ServiceProvider.find(tyin1);
        if (found == m_ServiceProvider.end())
            return nullptr;

        Ref<TServiceProvider<ServiceType>> tService = std::static_pointer_cast<typename TServiceProvider<ServiceType>>(found->second);
        return tService->Get();
    }
}