#pragma once
namespace Borg
{
    template <typename T>
    class IComparer
    {
    public:
        virtual ~IComparer() = default;
        virtual int Compare(T left, T right) const = 0;
    };

    template <typename TSource>
    class OrderEnumerator : public IEnumerator<TSource>
    {
    public:
        OrderEnumerator(Ref<IEnumerator<TSource>> enumerator, IComparer<TSource> *comparer)
            : m_ParentEnumerator(enumerator), m_comparer(comparer)
        {
        }

        TSource Current() const override
        {
            return m_VectorEnumerator->Current();
        }

        bool MoveNext() override
        {
            if (!m_VectorEnumerator)
            {
                std::vector<TSource> tempVec;
                while (m_ParentEnumerator->MoveNext())
                    tempVec.push_back(m_ParentEnumerator->Current());
                std::sort(tempVec.begin(), tempVec.end(), [this](const TSource& left, const TSource& right)
                          { return m_comparer->Compare(left, right) < 0; });
                m_VectorEnumerator = CreateRef<VectorEnumerator<TSource>>(tempVec);
            }
            return m_VectorEnumerator->MoveNext();
        }

        void Reset()
        {
            m_ParentEnumerator->Reset();
            m_VectorEnumerator = nullptr;
        }

    private:
        IComparer<TSource> *m_comparer;
        Ref<VectorEnumerator<TSource>> m_VectorEnumerator = nullptr;
        Ref<IEnumerator<TSource>> m_ParentEnumerator;
    };
}