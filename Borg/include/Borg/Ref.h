#pragma once
#include <memory>
//#include "Exception.h"

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
     * @brief Optional cast of TSource to TTarget. Will return null if the cast is not possible.
     *
     * @tparam TTarget
     * @tparam TSource
     * @param value
     * @return constexpr Ref<TTarget>
     */
    template <typename TTarget, typename TSource>
    constexpr Ref<TTarget> RefAs(TSource value)
    {
        return std::dynamic_pointer_cast<TTarget>(value);
    }

    template <typename TTarget, typename TSource>
    constexpr Ref<TTarget> RefCast(TSource value)
    {
        Ref<TTarget> target = std::dynamic_pointer_cast<TTarget>(value);
        // if (!target)
        //     throw InvalidCastException("Failed to cast TSource to TTarget");
        return target;
    }
}