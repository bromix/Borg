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

    template <typename TSource, typename TFunc, typename TReturn = std::invoke_result<TFunc, TSource>::type>
    class SelectEnumerator : public IEnumerator<TReturn>
    {
    public:
        SelectEnumerator(Ref<IEnumerator<TSource>> enumerator, TFunc func)
            : m_SelectFunc(func), m_ParentEnumerator(enumerator)
        {
        }

        TReturn Current() const override
        {
            return m_SelectFunc(m_ParentEnumerator->Current());
        }

        bool MoveNext() override
        {
            return m_ParentEnumerator->MoveNext();
        }

        void Reset()
        {
            m_ParentEnumerator->Reset();
        }

    private:
        Ref<IEnumerator<TSource>> m_ParentEnumerator;
        TFunc m_SelectFunc;
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
        LINQEnumerator<TReturn> Select(TFunc func)
        {
            return LINQEnumerator<TReturn>(CreateRef<SelectEnumerator<TSource, TFunc>>(m_Enumerator, func));
            ;
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