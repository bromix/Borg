#pragma once
#include "Ref.h"
#include <functional>

namespace Borg
{
    /**
     * @brief Encapsulates a method that has zero or more Args and returns a value of the type specified by the Result parameter.
     * https://docs.microsoft.com/en-us/dotnet/api/system.func-1
     * @tparam Result
     * @tparam Args
     */
    template <typename TResult, typename... TArgs>
    using Func = std::function<TResult(TArgs...args)>;

    /**
     * @brief Encapsulates a method that has zero or more Args and does not return a value.
     * https://docs.microsoft.com/en-us/dotnet/api/system.action
     * @tparam Args
     */
    template <typename... TArgs>
    using Action = std::function<void(TArgs...args)>;
}
