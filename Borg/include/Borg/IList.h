#pragma once
#include <vector>

namespace Borg
{
    template <typename T>
    class IList2
    {
    public:
        using Iterator = typename std::vector<T>::iterator;

        virtual ~IList2() = default;

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