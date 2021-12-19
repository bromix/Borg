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

        void Reset()
        {
            m_ParentEnumerator->Reset();
        }

    private:
        Ref<IEnumerator<TSource>> m_ParentEnumerator;
        TFunc m_SelectFunc;
    };
}