#pragma once
namespace Borg
{
    template <typename TSource, typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
    class SelectEnumerator : public IEnumerator<TResult>
    {
    public:
        SelectEnumerator(Ref<IEnumerator<TSource>> enumerator, TFunc func)
            : m_SelectFunc(func), m_ParentEnumerator(enumerator)
        {
        }

        TResult Current() const override
        {
            return m_SelectFunc(m_ParentEnumerator->Current());
        }

        bool MoveNext() override
        {
            return m_ParentEnumerator->MoveNext();
        }

    private:
        Ref<IEnumerator<TSource>> m_ParentEnumerator;
        TFunc m_SelectFunc;
    };

    template <typename TSource, typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
    class SelectEnumerable : public IEnumerable<TResult>
    {
    public:
        SelectEnumerable(Ref<IEnumerable<TSource>> innerEnumerable, TFunc selectFunction)
            : m_SelectFunction(selectFunction), m_InnerEnumerable(innerEnumerable)
        {
        }

        Ref<IEnumerator<TResult>> GetEnumerator() const override
        {
            return CreateRef<SelectEnumerator<TSource, TFunc>>(m_InnerEnumerable->GetEnumerator(), m_SelectFunction);
        }
    private:
        Ref<IEnumerable<TSource>> m_InnerEnumerable;
        TFunc m_SelectFunction;
    };
}