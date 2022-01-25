#pragma once
#include "ICollection.h"

namespace Borg
{
    template <typename T>
    class IList : public virtual ICollection<T>
    {
    public:
        virtual ~IList() = default;

        /**
         * @brief Gets or sets the element at the specified index.
         * 
         * @param index 
         * @return T& 
         */
        virtual T &operator[](int32_t index) = 0;
    };
}