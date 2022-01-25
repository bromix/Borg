#pragma once
#include "IList.h"
#include <vector>

namespace Borg
{
    template <typename T>
    class List : public virtual IList<T>
    {
    public:
        void Add(const T &item) override
        {
            m_List.push_back(item);
        }

        void Clear() override
        {
            m_List.clear();
        }

        int32_t GetCount() const override
        {
            return m_List.size();
        }

        T &operator[](int32_t index) override
        {
            return m_List[index];
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