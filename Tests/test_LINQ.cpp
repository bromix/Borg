#include "Borg/LINQ.h"
#include <gtest/gtest.h>
#include <vector>

using namespace Borg;

struct Person
{
    Person(const std::string& name, int age)
    {
        this->name = name;
        this->age = age;
    }

    std::string name = "";
    int age = 0;
};

TEST(LINQ, test)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers)
                      .Where([](int x) -> bool
                             { return x > 5; })
                      .Where([](int x) -> bool
                             { return x % 2 == 0; })
                      .ToVector();
}

TEST(LINQ, struct)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Peter", 24)
    };
    auto result = LINQ::From(persons)
                      .Where([](Ref<Person> x) -> bool
                             { return x->name == "Hans"; })
                      .ToVector();
}
