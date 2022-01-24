#pragma once
#include "ICollection.h"

namespace Borg
{
    template <typename T>
    class IList : public virtual ICollection<T>
    {
    public:
        virtual ~IList() = default;

        virtual void Add(const T &item) = 0;
    };
}