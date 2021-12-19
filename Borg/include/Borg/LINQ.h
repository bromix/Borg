#pragma once
#include "Types.h"
#include "StdEnumerators.h"
#include "IEnumerator.h"

namespace Borg
{
    template <typename T>
    class LambaEnumerator : public IEnumerator<T>
    {
    public:
        LambaEnumerator(Ref<IEnumerator<T>> enumerator, Func<bool, T> func)
            : m_Func(func), m_Enumerator(enumerator)
        {
        }

        T Current() const override
        {
            return m_Enumerator->Current();
        }

        bool MoveNext() override
        {
            while (m_Enumerator->MoveNext())
            {
                if (m_Func(m_Enumerator->Current()))
                    return true;
            }

            return false;
        }

        void Reset()
        {
            m_Enumerator->Reset();
        }

    private:
        Ref<IEnumerator<T>> m_Enumerator;
        Func<bool, T> m_Func;
    };

    template <typename T>
    class LINQEnumerator
    {
    public:
        LINQEnumerator(const Ref<IEnumerator<T>> &enumerator)
            : m_Enumerator(enumerator)
        {
        }

        ~LINQEnumerator() = default;

        LINQEnumerator<T> Where(Func<bool, T> filter)
        {
            return LINQEnumerator<T>(CreateRef<LambaEnumerator<T>>(m_Enumerator, filter));
        }

        template <typename F, typename Return = std::invoke_result<F, T>::type>
        std::vector<Return> Select(F func)
        {
            std::vector<Return> result;

            while(m_Enumerator->MoveNext())
            {
                Return t = func(m_Enumerator->Current());
                result.push_back(t);
            }

            return result;
        }

        std::vector<T> ToVector() const
        {
            std::vector<T> result;

            while (m_Enumerator->MoveNext())
                result.push_back(m_Enumerator->Current());

            return result;
        }

    private:
        Ref<IEnumerator<T>> m_Enumerator;
    };

    class LINQ
    {
    public:
        LINQ() = default;

        template <typename T>
        static LINQEnumerator<T> From(const std::vector<T> &input)
        {
            return LINQEnumerator<T>(CreateRef<VectorEnumerator<T>>(input));
        }
    };
}