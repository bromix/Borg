#pragma once
#include <stdint.h>
#include <functional>
#include <memory>

namespace Borg
{
    // Taken from Hazel.
    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief Encapsulates a method that has zero or more Args and returns a value of the type specified by the Result parameter.
     * https://docs.microsoft.com/en-us/dotnet/api/system.func-1
     * @tparam Result
     * @tparam Args
     */
    template <typename Result, typename... Args>
    using Func = std::function<Result(Args &&...args)>;

    /**
     * @brief Encapsulates a method that has zero or more Args and does not return a value.
     * https://docs.microsoft.com/en-us/dotnet/api/system.action
     * @tparam Args
     */
    template <typename... Args>
    using Action = std::function<void(Args &&...args)>;
}
