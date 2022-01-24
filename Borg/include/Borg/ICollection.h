#pragma once
#include "IIterator.h"

namespace Borg
{
    template <typename T>
    class ICollection : public virtual IIterator<T>
    {
    public:
        /**
         * @brief Gets the number of elements contained in the ICollection<T>.
         * 
         * @return int32_t 
         */
        virtual int32_t GetCount() const = 0;
    };
}