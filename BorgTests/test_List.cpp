#include "Borg/List.h"
#include "Borg/Ref.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(List, Add)
{
    Ref<IList<int>> numbers = CreateRef<List<int>>();
    numbers->Add(10);
}

TEST(List, ForLoop)
{
    //Ref<IList2<int>> numbers = CreateRef<List2<int>>();
    auto numbers = CreateRef<List<int>>();
    numbers->Add(10);
    numbers->Add(1);
    numbers->Add(11);

    for(auto number: *numbers)
    {
        auto x = 0;
    }
}
