#pragma once
#include "Types.h"
#include "IEnumerator.h"

namespace Borg
{
    template <typename T>
    class IEnumerable
    {
    public:
        virtual ~IEnumerable() = default;
        virtual Ref<IEnumerator<T>> GetEnumerator() const = 0;
    };
}