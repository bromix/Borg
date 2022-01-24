#pragma once
#include "IList.h"
#include <vector>

namespace Borg
{
    template<typename T>
    class IList: public std::vector<T>
    {
    };

    template<typename T>
    class List: public IList<T>
    {
    };

    template<typename T>
    class List2: public virtual IList2<T>
    {
    public:
        using Iterator = typename std::vector<T>::iterator;

        void Add(const T &item) override
        {
            m_List.push_back(item);
        }

        Iterator begin() noexcept
        {
            return m_List.begin();
        }

        Iterator end() noexcept
        {
            return m_List.end();
        }
    private:
        std::vector<T> m_List;
    };
}