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
    constexpr Ref<TTarget> RefAs(TSource value)
    {
        return std::dynamic_pointer_cast<TTarget>(value);
    }

    template <typename TTarget, typename TSource>
    constexpr Ref<TTarget> RefCast(TSource value)
    {
        Ref<TTarget> target = std::dynamic_pointer_cast<TTarget>(value);
        if (!target)
            throw InvalidCastException("Failed to cast TSource to TTarget");
        return target;
    }
}