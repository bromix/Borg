#pragma once

namespace Borg
{
    template <typename T>
    class IComparer
    {
    public:
        virtual ~IComparer() = default;
        virtual int Compare(const T& left, const T& right) const = 0;
    };
}