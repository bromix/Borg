#pragma once
#include "Types.h"
#include "StdEnumerators.h"
#include "IEnumerator.h"
#include "LINQ/WhereEnumerator.h"
#include "LINQ/SelectEnumerator.h"

namespace Borg
{
    template <typename TSource>
    class LINQEnumerator
    {
    public:
        LINQEnumerator(const Ref<IEnumerator<TSource>> &enumerator)
            : m_Enumerator(enumerator)
        {
        }

        ~LINQEnumerator() = default;

        /**
         * @brief Returns the number of elements in a sequence.
         *
         * @return uint32_t
         */
        uint32_t Count()
        {
            uint32_t count = 0;

            while (m_Enumerator->MoveNext())
                ++count;

            return count;
        }

        /**
         * @brief Returns an uint64 that represents the number of elements in a sequence.
         *
         * @return uint64_t
         */
        uint64_t LongCount()
        {
            uint32_t count = 0;

            while (m_Enumerator->MoveNext())
                ++count;

            return count;
        }

        /**
         * @brief Filters a sequence of values based on a predicate.
         *
         * @param predicate
         * @return LINQEnumerator<TSource>
         */
        LINQEnumerator<TSource> Where(Func<bool, TSource> predicate)
        {
            return LINQEnumerator<TSource>(CreateRef<WhereEnumerator<TSource>>(m_Enumerator, predicate));
        }

        /**
         * @brief Projects each element of a sequence into a new form.
         *
         * @tparam TFunc
         * @tparam TResult
         * @tparam TSource>::type
         * @param func
         * @return LINQEnumerator<TResult>
         */
        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQEnumerator<TResult> Select(TFunc func)
        {
            return LINQEnumerator<TResult>(CreateRef<SelectEnumerator<TSource, TFunc>>(m_Enumerator, func));
        }

        /**
         * @brief Sorts the elements of a sequence in ascending order.
         *
         * @tparam TFunc
         * @tparam TResult
         * @tparam TSource>::type
         * @param func
         * @return LINQEnumerator<TSource>
         */
        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQEnumerator<TSource> OrderBy(TFunc func)
        {
            auto orderedVector = ToVector();
            std::sort(orderedVector.begin(), orderedVector.end(), [func](TSource a, TSource b)
                      { return func(a) < func(b); });

            return LINQEnumerator<TSource>(CreateRef<VectorEnumerator<TSource>>(orderedVector));
        }

        /**
         * @brief Sorts the elements of a sequence in descending order.
         *
         * @tparam TFunc
         * @tparam TResult
         * @tparam TSource>::type
         * @param func
         * @return LINQEnumerator<TSource>
         */
        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQEnumerator<TSource> OrderByDescending(TFunc func)
        {
            auto orderedVector = ToVector();
            std::sort(orderedVector.begin(), orderedVector.end(), [func](TSource a, TSource b)
                      { return func(a) > func(b); });

            return LINQEnumerator<TSource>(CreateRef<VectorEnumerator<TSource>>(orderedVector));
        }

        /**
         * @brief Creates a std::vector<TSource> from an IEnumerable<T>.
         *
         * @return std::vector<TSource>
         */
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