#include "Borg/List.h"
#include "Borg/Ref.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(List, Add)
{
    List<int> numbers{};
    numbers.Add(10);
    ASSERT_EQ(1, numbers.GetCount());
}

TEST(List, ForLoop)
{
    //Ref<IList2<int>> numbers = CreateRef<List2<int>>();
    List<int> numbers{};
    numbers.Add(10);
    numbers.Add(1);
    numbers.Add(11);

    for(auto number: numbers)
    {
        auto x = 0;
    }
}

TEST(List, Index)
{
    List<int> numbers{};
    numbers.Add(10);
    numbers.Add(1);
    numbers.Add(11);

    ASSERT_EQ(10, numbers[0]);
    ASSERT_EQ(1, numbers[1]);
    ASSERT_EQ(11, numbers[2]);

    numbers[0] = 20;
    ASSERT_EQ(20, numbers[0]);
}
