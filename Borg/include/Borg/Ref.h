#pragma once
#include <memory>
#include "Exception.h"

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
    constexpr Ref<TTarget> RefAs(const Ref<TSource>& value)
    {
        return std::dynamic_pointer_cast<TTarget>(value);
    }

    template <typename TTarget, typename TSource>
    constexpr Ref<TTarget> RefCast(const Ref<TSource>& value)
    {
        Ref<TTarget> target = RefAs<TTarget>(value);
        if (!target)
            throw InvalidCastException("Failed to cast TSource to TTarget");
        return target;
    }

    template <typename TTarget>
    constexpr Ref<TTarget> RefAs(const Ref<void>& value)
    {
        return std::static_pointer_cast<TTarget>(value);
    }

    template <typename TTarget>
    constexpr Ref<TTarget> RefCast(const Ref<void>& value)
    {
        Ref<TTarget> target = RefAs<TTarget>(value);
        if (!target)
            throw InvalidCastException("Failed to cast TSource to TTarget");
        return target;
    }
}