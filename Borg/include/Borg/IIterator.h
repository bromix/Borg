#pragma once
#include <vector>

namespace Borg
{
    template <typename T>
    class IIterator
    {
    public:
        virtual ~IIterator() = default;

        using Iterator = typename std::vector<T>::iterator;

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
