#pragma once
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
}