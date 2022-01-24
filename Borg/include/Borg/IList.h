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
         * @brief Adds an item to the IList.
         * 
         * @param item 
         */
        virtual void Add(const T &item) = 0;

        /**
         * @brief Removes all items from the IList.
         */
        virtual void Clear() = 0;
    };
}