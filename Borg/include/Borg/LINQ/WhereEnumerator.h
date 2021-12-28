#pragma once
#include "Borg/IEnumerable.h"

namespace Borg
{
    template <typename TSource>
    class WhereEnumerator : public IEnumerator<TSource>
    {
    public:
        WhereEnumerator(Ref<IEnumerator<TSource>> innerEnumerator, Func<bool, TSource> predicate)
            : m_Predicate(predicate), m_InnerEnumerator(innerEnumerator)
        {
        }

        TSource Current() const override
        {
            return m_InnerEnumerator->Current();
        }

        bool MoveNext() override
        {
            while (m_InnerEnumerator->MoveNext())
            {
                if (m_Predicate(m_InnerEnumerator->Current()))
                    return true;
            }

            return false;
        }

    private:
        Ref<IEnumerator<TSource>> m_InnerEnumerator;
        Func<bool, TSource> m_Predicate;
    };

    template <typename TSource>
    class WhereEnumerable : public IEnumerable<TSource>
    {
    public:
        WhereEnumerable(Ref<IEnumerable<TSource>> innerEnumerable, Func<bool, TSource> predicate)
            : m_Predicate(predicate), m_InnerEnumerable(innerEnumerable)
        {
        }

        Ref<IEnumerator<TSource>> GetEnumerator() const override
        {
            return CreateRef<WhereEnumerator<TSource>>(m_InnerEnumerable->GetEnumerator(), m_Predicate);
        }

    private:
        Ref<IEnumerable<TSource>> m_InnerEnumerable;
        Func<bool, TSource> m_Predicate;
    };
}