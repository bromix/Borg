#pragma once
#include <vector>

namespace Borg
{
    template <typename T>
    class List
    {
    public:
        using Iterator = typename std::vector<T>::iterator;

        void Add(const T &item)
        {
            m_List.push_back(item);
        }

        void Clear()
        {
            m_List.clear();
        }

        int32_t GetCount() const
        {
            return m_List.size();
        }

        T &operator[](int32_t index)
        {
            return m_List[index];
        }

        Iterator begin()
        {
            return m_List.begin();
        }

        Iterator end()
        {
            return m_List.end();
        }

    private:
        std::vector<T> m_List;
    };
}