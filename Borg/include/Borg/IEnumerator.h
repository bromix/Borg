#pragma once
#include "Types.h"

namespace Borg
{
    template <typename T>
    class IEnumerator
    {
    public:
        virtual ~IEnumerator() = default;
        virtual T Current() const = 0;
        virtual bool MoveNext() = 0;
    };
}