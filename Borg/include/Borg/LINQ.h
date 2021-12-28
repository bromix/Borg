#pragma once
#include "Types.h"
#include "RefCast.h"
#include "StdEnumerators.h"
#include "IEnumerable.h"
#include "LINQ/WhereEnumerator.h"
#include "LINQ/SelectEnumerator.h"
#include "LINQ/OrderEnumerator.h"

namespace Borg
{
    template <typename TSource>
    class LINQOrderedEnumerator;

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
        LINQOrderedEnumerator<TSource> OrderBy(TFunc func)
        {
            return LINQOrderedEnumerator<TSource>(m_Enumerator, func);
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
        LINQOrderedEnumerator<TSource> OrderByDescending(TFunc func)
        {
            return LINQOrderedEnumerator<TSource>(m_Enumerator, func);
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

    protected:
        Ref<IEnumerator<TSource>> m_Enumerator;
    };

    template <typename TSource>
    class LINQOrderedEnumerator : public LINQEnumerator<TSource>, public IComparer<TSource>
    {
    public:
        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQOrderedEnumerator(const Ref<IEnumerator<TSource>> &enumerator, TFunc func)
            : LINQEnumerator<TSource>(CreateRef<OrderEnumerator<TSource>>(enumerator, this))
        {
            m_Comparer.push_back(AddComparer<TFunc>(func));
        }

        ~LINQOrderedEnumerator() = default;

        int Compare(TSource left, TSource right) const
        {
            for (auto comparer : m_Comparer)
            {
                if (comparer(left, right) < 0)
                    return -1;
                if (comparer(left, right) > 0)
                    return 1;
            }
            return 0;
        }

        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQOrderedEnumerator<TSource> ThenBy(TFunc func)
        {
            m_Comparer.push_back(AddComparer<TFunc>(func));
            return *this;
        }

    private:
        template <typename TFunc>
        auto AddComparer(TFunc func)
        {
            return [func](const TSource &left, const TSource &right)
            {
                auto rleft = func(left);
                auto rright = func(right);

                if (rleft < rright)
                    return -1;
                if (rleft > rright)
                    return 1;
                return 0;
            };
        }
        std::vector<Func<int, const TSource &, const TSource &>> m_Comparer;
    };

    template <typename TSource>
    class LINQEnumberable : public IEnumerable<TSource>
    {
    public:
        LINQEnumberable(const Ref<IEnumerable<TSource>> &innerEnumerable) : m_InnerEnumerable(innerEnumerable) {}
        Ref<IEnumerator<TSource>> GetEnumerator() const override
        {
            return m_InnerEnumerable->GetEnumerator();
        }

        uint32_t Count() const
        {
            uint32_t count = 0;
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
                ++count;
            return count;
        }

        uint64_t LongCount() const
        {
            uint64_t count = 0;
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
                ++count;
            return count;
        }

        LINQEnumberable<TSource> Where(Func<bool, TSource> predicate)
        {
            return LINQEnumberable<TSource>(CreateRef<WhereEnumerable<TSource>>(m_InnerEnumerable, predicate));
        }

        std::vector<TSource> ToVector() const
        {
            std::vector<TSource> result;

            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
                result.push_back(enumerator->Current());

            return result;
        }

    private:
        Ref<IEnumerable<TSource>> m_InnerEnumerable;
    };

    class LINQ
    {
    public:
        LINQ() = default;

        template <typename T>
        static LINQEnumberable<T> From(const std::vector<T> &input)
        {
            return LINQEnumberable<T>(CreateRef<VectorEnumerable<T>>(input));
        }
    };
}