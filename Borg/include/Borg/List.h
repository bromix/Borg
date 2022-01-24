#pragma once
#include <vector>

namespace Borg
{
    template<typename T>
    class IList: public std::vector<T>
    {
    };

    template<typename T>
    class List: public IList<T>
    {
    };
}