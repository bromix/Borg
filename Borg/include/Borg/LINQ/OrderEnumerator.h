#pragma once
#include "Borg/IComparer.h"

namespace Borg
{
    template <typename TSource>
    class OrderEnumerable : public IEnumerable<TSource>
    {
    public:
        OrderEnumerable(const Ref<IEnumerable<TSource>>& innerEnumerable, const Ref<IComparer<TSource>>& comparer)
            : m_InnerEnumerable(innerEnumerable), m_Comparer(comparer)
        {
        }

        Ref<IEnumerator<TSource>> GetEnumerator() const override
        {
            std::vector<TSource> container;
            auto enumerator = m_InnerEnumerable->GetEnumerator();
            while (enumerator->MoveNext())
                container.push_back(enumerator->Current());

            // Sort vector via delegate.
            std::sort(container.begin(), container.end(), [this](const TSource &left, const TSource &right)
                      { return m_Comparer->Compare(left, right) < 0; });

            return CreateRef<VectorEnumerator<TSource>>(container);
        }

    private:
        Ref<IEnumerable<TSource>> m_InnerEnumerable;
        Ref<IComparer<TSource>> m_Comparer;
    };
}