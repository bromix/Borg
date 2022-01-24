#pragma once
#include "IList.h"
#include <vector>

namespace Borg
{
    template <typename T>
    class IList : public std::vector<T>
    {
    };

    template <typename T>
    class List : public IList<T>
    {
    };

    template <typename T>
    class List2 : public virtual IList2<T>
    {
    public:
        void Add(const T &item) override
        {
            m_List.push_back(item);
        }
    protected:
        Iterator doBegin() override
        {
            return m_List.begin();
        }
        
        Iterator doEnd() override
        {
            return m_List.end();
        }
    private:
        std::vector<T> m_List;
    };
}