#pragma once
#include <optional>
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
    class LINQOrderedEnumberable;

    template <typename TSource>
    class LINQComparer;

    template <typename TSource>
    class LINQEnumberable : public IEnumerable<TSource>
    {
    public:
        LINQEnumberable(const Ref<IEnumerable<TSource>> &innerEnumerable) : m_InnerEnumerable(innerEnumerable) {}

        Ref<IEnumerator<TSource>> GetEnumerator() const override
        {
            return m_InnerEnumerable->GetEnumerator();
        }

        /**
         * @brief Returns the number of elements in a sequence.
         *
         * @return uint32_t
         */
        uint32_t Count() const
        {
            uint32_t count = 0;
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
                ++count;
            return count;
        }

        /**
         * @brief Returns a number that represents how many elements in the specified sequence satisfy a condition.
         *
         * @param predicate
         * @return uint32_t
         */
        uint32_t Count(Func<bool, TSource> predicate)
        {
            uint32_t count = 0;
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
            {
                if (predicate(enumerator->Current()))
                    ++count;
            }
            return count;
        }

        /**
         * @brief Returns an uint64_t that represents the number of elements in a sequence.
         *
         * @return uint64_t
         */
        uint64_t LongCount() const
        {
            uint64_t count = 0;
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
                ++count;
            return count;
        }

        /**
         * @brief Returns an uint64_t that represents how many elements in a sequence satisfy a condition.
         *
         * @param predicate
         * @return uint64_t
         */
        uint64_t LongCount(Func<bool, TSource> predicate)
        {
            uint64_t count = 0;
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
            {
                if (predicate(enumerator->Current()))
                    ++count;
            }
            return count;
        }

        /**
         * @brief Returns the first element of a sequence.
         *
         * @return TSource
         */
        TSource First() const
        {
            auto enumerator = GetEnumerator();
            if (enumerator->MoveNext())
                return enumerator->Current();

            throw InvalidOperationException("No element satisfies the condition");
        }

        /**
         * @brief Returns the first element in a sequence that satisfies a specified condition.
         *
         * @param predicate
         * @return TSource
         */
        TSource First(Func<bool, TSource> predicate) const
        {
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
            {
                if (predicate(enumerator->Current()))
                    return enumerator->Current();
            }

            throw InvalidOperationException("No element satisfies the condition");
        }

        /**
         * @brief Returns the last element of a sequence.
         *
         * @return TSource
         */
        TSource Last() const
        {
            auto enumerator = GetEnumerator();
            std::optional<TSource> result;
            while (enumerator->MoveNext())
                result = enumerator->Current();

            if (result.has_value())
                return result.value();

            throw InvalidOperationException("No element satisfies the condition");
        }

        /**
         * @brief Returns the last element of a sequence that satisfies a specified condition.
         *
         * @param predicate
         * @return TSource
         */
        TSource Last(Func<bool, TSource> predicate) const
        {
            auto enumerator = GetEnumerator();
            std::optional<TSource> result;
            while (enumerator->MoveNext())
            {
                if (predicate(enumerator->Current()))
                    result = enumerator->Current();
            }

            if (result.has_value())
                return result.value();

            throw InvalidOperationException("No element satisfies the condition");
        }

        /**
         * @brief Determines whether all elements of a sequence satisfy a condition.
         *
         * @param predicate
         * @return true
         * @return false
         */
        bool All(Func<bool, TSource> predicate) const
        {
            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
            {
                if (!predicate(enumerator->Current()))
                    return false;
            }

            return true;
        }

        /**
         * @brief Filters a sequence of values based on a predicate.
         *
         * @param predicate
         * @return LINQEnumberable<TSource>
         */
        LINQEnumberable<TSource> Where(Func<bool, TSource> predicate)
        {
            return LINQEnumberable<TSource>(CreateRef<WhereEnumerable<TSource>>(m_InnerEnumerable, predicate));
        }

        /**
         * @brief Projects each element of a sequence into a new form.
         *
         * @tparam TFunc
         * @tparam TResult
         * @tparam TSource>::type
         * @param func
         * @return LINQEnumberable<TResult>
         */
        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQEnumberable<TResult> Select(TFunc func)
        {
            return LINQEnumberable<TResult>(CreateRef<SelectEnumerable<TSource, TFunc>>(m_InnerEnumerable, func));
        }

        /**
         * @brief Creates a std::vector<TSource>.
         *
         * @return std::vector<TSource>
         */
        std::vector<TSource> ToVector() const
        {
            std::vector<TSource> result;

            auto enumerator = GetEnumerator();
            while (enumerator->MoveNext())
                result.push_back(enumerator->Current());

            return result;
        }

        template <typename TFunc, typename TResult = std::invoke_result<TFunc, TSource>::type>
        LINQOrderedEnumberable<TSource> OrderBy(TFunc selectFunction)
        {
            /*
            LINQOrderedEnumberable and OrderEnumerable share the same
            instance of LINQComparer.
            In LINQOrderedEnumberable we can add additional comparer/
            selector functions. The OrderEnumerable will call the
            LINQComparer for sorting.
            */
            auto comparer = CreateRef<LINQComparer<TSource>>();
            comparer->AddSelectorForSort(selectFunction);

            auto orderEnumerable = CreateRef<OrderEnumerable<TSource>>(m_InnerEnumerable, comparer);

            return LINQOrderedEnumberable<TSource>(orderEnumerable, comparer);
        }

    protected:
        Ref<IEnumerable<TSource>> m_InnerEnumerable;
    };

    template <typename TSource>
    class LINQComparer : public IComparer<TSource>
    {
    public:
        int Compare(const TSource &left, const TSource &right) const override
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

        template <typename TFunc>
        void AddSelectorForSort(TFunc selectFunction)
        {
            auto sortFunction = [selectFunction](const TSource &left, const TSource &right)
            {
                auto selectLeft = selectFunction(left);
                auto selectRight = selectFunction(right);

                if (selectLeft < selectRight)
                    return -1;
                if (selectLeft > selectRight)
                    return 1;
                return 0;
            };

            m_Comparer.push_back(sortFunction);
        }

    private:
        std::vector<Func<int, const TSource &, const TSource &>> m_Comparer;
    };

    template <typename TSource>
    class LINQOrderedEnumberable : public LINQEnumberable<TSource>
    {
    public:
        LINQOrderedEnumberable(const Ref<IEnumerable<TSource>> &innerEnumerable, const Ref<LINQComparer<TSource>> &comparer)
            : LINQEnumberable<TSource>(innerEnumerable), m_Comparer(comparer)
        {
        }

        template <typename TFunc>
        LINQOrderedEnumberable<TSource> ThenBy(TFunc selectFunction)
        {
            m_Comparer->AddSelectorForSort(selectFunction);
            return *this;
        }

    private:
        Ref<LINQComparer<TSource>> m_Comparer;
    };

    class LINQ
    {
    public:
        LINQ() = default;

        template <typename T>
        static LINQEnumberable<T> From(std::initializer_list<T> input)
        {
            return LINQEnumberable<T>(CreateRef<VectorEnumerable<T>>(input));
        }

        template <typename T>
        static LINQEnumberable<T> From(const std::vector<T> &input)
        {
            return LINQEnumberable<T>(CreateRef<VectorEnumerable<T>>(input));
        }

        template <typename T>
        static LINQEnumberable<T> From(std::vector<T> &&input)
        {
            return LINQEnumberable<T>(CreateRef<VectorEnumerable<T>>(std::move(input)));
        }
    };
}