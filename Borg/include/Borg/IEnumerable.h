#pragma once
#include "Types.h"

namespace Borg
{
    template<typename T>
    class IEnumerable
    {
        public:
            virtual ~IEnumerable() = default;
            virtual Ref<T> GetEnumerator() const = 0;
    };
}