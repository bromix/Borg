#pragma once
#include "IEnumerable.h"

namespace Borg
{
    template <typename T>
    class VectorEnumerator : public IEnumerator<T>
    {
    public:
        VectorEnumerator(const std::vector<T> &input)
            : m_Vector(input)
        {
        }

        T Current() const override
        {
            return m_Vector.at(m_Index);
        }

        bool MoveNext() override
        {
            ++m_Index;
            if (m_Index < m_Vector.size())
                return true;
            return false;
        }

        void Reset()
        {
            m_Index = -1;
        }

    private:
        int m_Index = -1;
        std::vector<T> m_Vector;
    };

    template <typename T>
    class VectorEnumerable : public IEnumerable<T>
    {
    public:
        VectorEnumerable(const std::vector<T> &input) : m_Vector(input){}
        VectorEnumerable(std::vector<T> &&input) : m_Vector(std::move(input)){}

        Ref<IEnumerator<T>> GetEnumerator() const override
        {
            return CreateRef<VectorEnumerator<T>>(m_Vector);
        }
    private:
        std::vector<T> m_Vector;
    };
}