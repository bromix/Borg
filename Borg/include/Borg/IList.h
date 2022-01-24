#pragma once
#include <vector>

namespace Borg
{
    template <typename T>
    class IList
    {
    public:
        using Iterator = typename std::vector<T>::iterator;

        virtual ~IList() = default;

        virtual void Add(const T &item) = 0;

        Iterator begin() noexcept
        {
            return doBegin();
        }

        Iterator end() noexcept
        {
            return doEnd();
        }

    protected:
        virtual Iterator doBegin() = 0;
        virtual Iterator doEnd() = 0;
    };
}