#include <typeindex>
#include <map>
#include <functional>
#include "Types.h"

namespace Borg
{
    template <typename ServiceType>
    using ServiceContructorFunc = std::function<Ref<ServiceType>()>;

    /**
     * @brief Base interface to derive each generic service type from.
     */
    class IService
    {
    };

    template <typename T>
    class TService : public IService
    {
    public:
        TService(ServiceContructorFunc<T> ctr) : m_Ctr(std::move(ctr)) {}

        Ref<T> Get();

    private:
        ServiceContructorFunc<T> m_Ctr;
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
        std::map<std::type_index, Ref<IService>> m_Services;
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

        ServiceContructorFunc<ServiceType> singletonGetter = [=]() -> Ref<ServiceType>
        {
            static Ref<ServiceType> _service = CreateRef<ImplementationType>(std::forward<Args>(args)...);
            return _service;
        };

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(singletonGetter);
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

        ServiceContructorFunc<ServiceType> scopedGetter = [=]() -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>(std::forward<Args>(args)...);
        };

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(scopedGetter);
    }

    template <typename ServiceType>
    Ref<ServiceType> ServiceCollection::GetService()
    {
        auto tyin1 = std::type_index(typeid(ServiceType));
        auto found = m_Services.find(tyin1);
        if (found == m_Services.end())
            return nullptr;

        auto tService = std::static_pointer_cast<typename TService<ServiceType>>(found->second);
        return tService->Get();
    }

    template <typename T>
    Ref<T> TService<T>::Get()
    {
        return m_Ctr();
    }
}