#pragma once
namespace Borg
{
    template <typename TSource>
    class WhereEnumerator : public IEnumerator<TSource>
    {
    public:
        WhereEnumerator(Ref<IEnumerator<TSource>> enumerator, Func<bool, TSource> predicate)
            : m_Predicate(predicate), m_ParentEnumerator(enumerator)
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
                if (m_Predicate(m_ParentEnumerator->Current()))
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
        Func<bool, TSource> m_Predicate;
    };
}