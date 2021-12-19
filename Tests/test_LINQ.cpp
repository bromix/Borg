#include "Borg/LINQ.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace Borg;

class Person
{
public:
    Person(const std::string &name, int age)
    {
        this->name = name;
        this->age = age;
    }

    std::string name = "";
    int age = 0;
};

TEST(LINQ, Count)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers).Count();
    ASSERT_EQ(10, result);
}

TEST(LINQ, Where)
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
        CreateRef<Person>("Peter", 24)};
    auto result = LINQ::From(persons)
                      .Where([](Ref<Person> x) -> bool
                             { return x->name == "Hans"; })
                      .ToVector();
}

TEST(LINQ, OrderBy)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Detlef", 35),
        CreateRef<Person>("Adam", 24)};
    auto result = LINQ::From(persons)
                      .OrderBy([](Ref<Person> x)
                               { return x->name; })
                      .ToVector();
}

TEST(LINQ, OrderByDescending)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Detlef", 35),
        CreateRef<Person>("Adam", 24)};
    auto result = LINQ::From(persons)
                      .OrderByDescending([](Ref<Person> x)
                               { return x->name; })
                      .ToVector();
}

TEST(LINQ, select)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Peter", 24)};

    auto result = LINQ::From(persons)
                      .Select([](Ref<Person> x) -> auto { return x->age; })
                      .ToVector();
}

TEST(LINQ, WhereAndSelect)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Peter", 24)};

    auto result = LINQ::From(persons)
                      .Where([](Ref<Person> x) -> bool
                             { return x->name == "Hans"; })
                      .Select([](Ref<Person> x) -> auto { return x->age; })
                      .ToVector();
}