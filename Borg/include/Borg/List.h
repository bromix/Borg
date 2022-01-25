#pragma once
#include <vector>

namespace Borg
{
    template <typename T>
    class List
    {
    public:
        using Iterator = typename std::vector<T>::iterator;

        List() = default;
        List(std::vector<T> &&vec) : m_List(std::move(vec)) {}

        /**
         * @brief Adds an object to the end of the List<T>.
         * 
         * @param item 
         */
        void Add(const T &item)
        {
            m_List.push_back(item);
        }

        /**
         * @brief Removes all elements from the List<T>.
         */
        void Clear()
        {
            m_List.clear();
        }

        /**
         * @brief Gets the number of elements contained in the List<T>.
         * 
         * @return int32_t 
         */
        int32_t GetCount() const
        {
            return m_List.size();
        }

        /**
         * @brief Gets or sets the element at the specified index.
         * 
         * @param index 
         * @return T& 
         */
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