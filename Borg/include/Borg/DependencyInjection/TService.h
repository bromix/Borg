#pragma once

namespace Borg::DependencyInjection
{

    /**
     * @brief Specialized service to hold the getter of the service.
     * @tparam T
     */
    template <typename ServiceType>
    class TService : public IService
    {
    public:
        TService(GetServiceWithProvider<ServiceType> &&getServiceCallback, ServiceLifetime lifetime)
            : IService(std::move(getServiceCallback), lifetime)
        {
        }

        ~TService()
        {
        }

        template <typename ImplementationType>
        static Ref<IService> CreateService(ServiceLifetime lifetime)
        {
            IsClass<ImplementationType>();

            /**
             * @brief Lambda to create a new instance of the service implemenation without the usage of the service provider.
             */
            auto createService = [](const ServiceProvider &) -> Ref<ServiceType>
            {
                return CreateRef<ImplementationType>();
            };
            return CreateRef<TService<ImplementationType>>(std::move(createService), lifetime);
        }

        template <typename ServiceType, typename ImplementationType>
        static Ref<IService> CreateService(ServiceLifetime lifetime)
        {
            IsInterface<ServiceType>();
            Implements<ServiceType, ImplementationType>();
            IsClass<ImplementationType>();

            /**
             * @brief Lambda to create a new instance of the service implemenation without the usage of the service provider.
             */
            auto createService = [](const ServiceProvider &) -> Ref<ServiceType>
            {
                return CreateRef<ImplementationType>();
            };
            return CreateRef<TService<ServiceType>>(std::move(createService), lifetime);
        }

        template <typename ServiceType>
        static Ref<IService> CreateService(GetServiceWithProvider<ServiceType> &&callback, ServiceLifetime lifetime)
        {
            /**
             * @brief Lambda to get a new instance of the service implemenation with the usage of the service provider.
             */
            auto callServiceCallback = [callback](const ServiceProvider &serviceProvider) -> Ref<ServiceType>
            {
                return callback(serviceProvider);
            };
            return CreateRef<TService<ServiceType>>(std::move(callServiceCallback), lifetime);
        }

        template <typename ServiceType>
        static Ref<IService> CreateService(GetService<ServiceType> &&callback, ServiceLifetime lifetime)
        {
            /**
             * @brief Lambda to get a new instance of the service implemenation.
             */
            auto callServiceCallback = [callback](const ServiceProvider &serviceProvider) -> Ref<ServiceType>
            {
                return callback();
            };
            return CreateRef<TService<ServiceType>>(std::move(callServiceCallback), lifetime);
        }
    };

}