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

    template<typename Result, typename... Args>
    using Func = std::function<Result(Args &&...args)>;
    
    template<typename... Args>
    using Action = std::function<void(Args &&...args)>;

    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;
}