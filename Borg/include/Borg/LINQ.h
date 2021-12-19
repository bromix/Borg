#pragma once
#include "Types.h"
#include "StdEnumerators.h"
#include "IEnumerator.h"

namespace Borg
{
    template <typename TSource>
    class WhereEnumerator : public IEnumerator<TSource>
    {
    public:
        WhereEnumerator(Ref<IEnumerator<TSource>> enumerator, Func<bool, TSource> whereFunc)
            : m_WhereFunc(whereFunc), m_ParentEnumerator(enumerator)
        {
        }

        TSource Current() const override
        {
            return m_ParentEnumerator->Current();
        }

        bool MoveNext() override
        {
            while (m_ParentEnumerator->MoveNext())
            {
                if (m_WhereFunc(m_ParentEnumerator->Current()))
                    return true;
            }

            return false;
        }

        void Reset()
        {
            m_ParentEnumerator->Reset();
        }

    private:
        Ref<IEnumerator<TSource>> m_ParentEnumerator;
        Func<bool, TSource> m_WhereFunc;
    };

    template <typename TSource>
    class LINQEnumerator
    {
    public:
        LINQEnumerator(const Ref<IEnumerator<TSource>> &enumerator)
            : m_Enumerator(enumerator)
        {
        }

        ~LINQEnumerator() = default;

        int Count()
        {
            auto count = 0;

            while (m_Enumerator->MoveNext())
                ++count;

            return count;
        }

        LINQEnumerator<TSource> Where(Func<bool, TSource> filter)
        {
            return LINQEnumerator<TSource>(CreateRef<WhereEnumerator<TSource>>(m_Enumerator, filter));
        }

        template <typename TFunc, typename TReturn = std::invoke_result<TFunc, TSource>::type>
        std::vector<TReturn> Select(TFunc func)
        {
            std::vector<TReturn> result;

            while (m_Enumerator->MoveNext())
            {
                TReturn t = func(m_Enumerator->Current());
                result.push_back(t);
            }

            return result;
        }

        std::vector<TSource> ToVector() const
        {
            std::vector<TSource> result;

            while (m_Enumerator->MoveNext())
                result.push_back(m_Enumerator->Current());

            return result;
        }

    private:
        Ref<IEnumerator<TSource>> m_Enumerator;
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