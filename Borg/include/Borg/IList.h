#pragma once

namespace Borg
{
    template<typename T>
    class IList2
    {
    public:
        virtual ~IList2() = default;

        virtual void Add(const T &item) = 0;
    };
}