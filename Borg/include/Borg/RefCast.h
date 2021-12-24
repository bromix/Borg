#pragma once
#include <memory>
#include "Exception.h"

namespace Borg
{

    /**
     * @brief Optional cast of TSource to TTarget. Will return null if the cast is not possible.
     *
     * @tparam TTarget
     * @tparam TSource
     * @param value
     * @return constexpr Ref<TTarget>
     */
    template <typename TTarget, typename TSource>
    constexpr Ref<TTarget> RefAs(Ref<TSource> value)
    {
        return std::dynamic_pointer_cast<TTarget>(value);
    }

    template <typename TTarget, typename TSource>
    constexpr Ref<TTarget> RefCast(Ref<TSource> value)
    {
        auto rest = std::is_void<TSource>::value;
        Ref<TTarget> target = RefAs<TTarget>(value);
        if (!target)
            throw InvalidCastException("Failed to cast TSource to TTarget");
        return target;
    }

    template <typename TTarget>
    constexpr Ref<TTarget> RefAs(Ref<void> value)
    {
        return std::static_pointer_cast<TTarget>(value);
    }

    template <typename TTarget>
    constexpr Ref<TTarget> RefCast(Ref<void> value)
    {
        Ref<TTarget> target = RefAs<TTarget>(value);
        if (!target)
            throw InvalidCastException("Failed to cast TSource to TTarget");
        return target;
    }
}