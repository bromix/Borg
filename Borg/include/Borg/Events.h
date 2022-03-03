#pragma once
#include "Types.h"
#include <future>
#include <cstdint>

/*
Based on
https://www.codeproject.com/Articles/1256352/CppEvent-How-to-Implement-Events-using-Standard-Cp
*/
namespace Borg
{
    template <typename... Args>
    class EventHandler
    {
    public:
        using FunctionType = Action<Args...>;

        explicit EventHandler(const EventHandler::FunctionType &handlerFunction)
            : m_HandlerFunction(handlerFunction)
        {
            m_Id = ++m_IdCounter;
        }

        EventHandler(const EventHandler &other) : m_HandlerFunction(other.m_HandlerFunction), m_Id(other.m_Id) {}
        EventHandler(EventHandler &&other) : m_HandlerFunction(std::move(other.m_HandlerFunction)), m_Id(other.m_Id) {}

        void operator()(Args... args) const
        {
            if (m_HandlerFunction)
            {
                m_HandlerFunction(args...);
            }
        }

        EventHandler &operator=(const EventHandler &rhs)
        {
            m_HandlerFunction = rhs.m_HandlerFunction;
            m_Id = rhs.m_Id;
            return *this;
        }

        EventHandler &operator=(EventHandler &&rhs)
        {
            std::swap(m_HandlerFunction, rhs.m_HandlerFunction);
            std::swap(m_Id, rhs.m_Id);
            return *this;
        }

        bool operator==(const EventHandler &rhs) const
        {
            return m_Id == rhs.m_Id;
        }

        bool operator!=(const EventHandler &rhs) const
        {
            return !(*this == rhs);
        }

        uint32_t Id() const
        {
            return m_Id;
        }

    private:
        uint32_t m_Id;
        EventHandler::FunctionType m_HandlerFunction;
        static std::atomic<uint32_t> m_IdCounter;
    };

    template <typename... Args>
    std::atomic<uint32_t> EventHandler<Args...>::m_IdCounter(0);

    template <typename... Args>
    class Event
    {
    public:
        using HandlerType = EventHandler<Args...>;

        Event() = default;

        Event(const Event &other)
        {
            std::lock_guard<std::mutex> lock(other.m_HandlersLock);
            m_Handlers = other.m_Handlers;
        }

        Event(Event &&other)
        {
            std::lock_guard<std::mutex> lock(other.m_HandlersLock);
            m_Handlers = std::move(other.m_Handlers);
        }

        Event &operator=(const Event &rhs)
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);
            std::lock_guard<std::mutex> lock2(rhs.m_HandlersLock);

            m_Handlers = rhs.m_Handlers;

            return *this;
        }

        Event &operator=(Event &&rhs)
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);
            std::lock_guard<std::mutex> lock2(rhs.m_HandlersLock);

            std::swap(m_Handlers, rhs.m_Handlers);

            return *this;
        }

        uint32_t Add(const HandlerType &handler)
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);

            m_Handlers.push_back(handler);
            return handler.Id();
        }

        uint32_t Add(typename const HandlerType::FunctionType &handlerFunction)
        {
            return Add(HandlerType(handlerFunction));
        }

        bool Remove(const HandlerType &handler)
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);

            auto it = std::find(m_Handlers.begin(), m_Handlers.end(), handler);
            if (it != m_Handlers.end())
            {
                m_Handlers.erase(it);
                return true;
            }

            return false;
        }

        bool RemoveId(const uint32_t &handlerId)
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);

            auto it = std::find_if(m_Handlers.begin(), m_Handlers.end(),
                                   [handlerId](const HandlerType &handler)
                                   { return handler.Id() == handlerId; });
            if (it != m_Handlers.end())
            {
                m_Handlers.erase(it);
                return true;
            }

            return false;
        }

        /**
         * @brief Clear all handlers
         */
        void Clear()
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);
            m_Handlers.clear();
        }

        void Call(Args... args) const
        {
            auto handlersCopy = getHandlersAsCopy();
            callImpl(handlersCopy, args...);
        }

        inline void operator()(Args... args) const
        {
            Call(args...);
        }

        inline uint32_t operator+=(const HandlerType &handler)
        {
            return Add(handler);
        }

        inline uint32_t operator+=(const typename HandlerType::FunctionType &handler)
        {
            return Add(handler);
        }

        inline bool operator-=(const HandlerType &handler)
        {
            return Remove(handler);
        }

        std::future<void> CallAsync(Args... args) const
        {
            return std::async(
                std::launch::async, [this](Args... asyncArgs)
                { Call(asyncArgs...); },
                args...);
        }

        operator bool() const
        {
            return !m_Handlers.empty();
        }

    private:
        std::vector<HandlerType> getHandlersAsCopy() const
        {
            std::lock_guard<std::mutex> lock(m_HandlersLock);

            // Since the function return value is by copy,
            // before the function returns (and destruct the lock_guard object),
            // it creates a copy of the m_handlers container.
            return m_Handlers;
        }

        void callImpl(const std::vector<HandlerType> &handlers, Args... args) const
        {
            for (const HandlerType &handler : handlers)
            {
                handler(args...);
            }
        }

        mutable std::mutex m_HandlersLock;
        std::vector<HandlerType> m_Handlers;
    };
}