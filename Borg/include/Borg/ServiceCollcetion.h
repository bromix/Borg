#include <typeindex>
#include <map>
#include <functional>
#include "Types.h"

namespace Borg
{
    class IService
    {
    public:
    };

    template <typename T>
    class TService : public IService
    {
    public:
        TService(std::function<Ref<T>()> ctr): m_Ctr(ctr){}

        Ref<T> Create();

    private:
        Ref<T> m_Service = nullptr;
        std::function<Ref<T>()> m_Ctr;
    };

    class ServiceCollection
    {
    public:
        template <typename ServiceType, typename ImplementationType>
        void AddSingleton();

        template <typename ServiceType, typename ImplementationType, typename... Args>
        void AddSingleton(Args &&...args);

        template <typename ServiceType>
        Ref<ServiceType> GetService();

    private:
        std::map<std::type_index, Ref<IService>> m_Services;
    };

    template <typename ServiceType, typename ImplementationType>
    void ServiceCollection::AddSingleton()
    {
        auto tyin1 = std::type_index(typeid(ServiceType));
        auto tyin2 = std::type_index(typeid(ImplementationType));

        auto tyhash1 = tyin1.hash_code();
        auto tyhash2 = tyin2.hash_code();

        auto createBla = [=]() -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>();
        };

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(createBla);
    }

    template <typename ServiceType, typename ImplementationType, typename... Args>
    void ServiceCollection::AddSingleton(Args &&...args)
    {
        auto tyin1 = std::type_index(typeid(ServiceType));
        auto tyin2 = std::type_index(typeid(ImplementationType));

        auto tyhash1 = tyin1.hash_code();
        auto tyhash2 = tyin2.hash_code();

        auto createBla = [=]() -> Ref<ServiceType>
        {
            return CreateRef<ImplementationType>(std::forward<Args>(args)...);
        };

        m_Services[tyin1] = CreateRef<TService<ServiceType>>(createBla);
    }

    template <typename ServiceType>
    Ref<ServiceType> ServiceCollection::GetService()
    {
        auto tyin1 = std::type_index(typeid(ServiceType));
        auto found = m_Services.find(tyin1);
        if (found == m_Services.end())
            return nullptr;

        auto tService = std::static_pointer_cast<typename TService<ServiceType>>(found->second);
        return tService->Create();
    }

    template <typename T>
    Ref<T> TService<T>::Create()
    {
        if(!m_Service)
        {
            m_Service = m_Ctr();
        }
        return m_Service;
    }
}