#include "Borg/LINQ.h"
#include <gtest/gtest.h>
#include <vector>

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
        CreateRef<Person>("Peter", 24)};
    auto result = LINQ::From(persons)
                      .Where([](Ref<Person> x) -> bool
                             { return x->name == "Hans"; })
                      .ToVector();
}

template <typename Source, typename Target>
std::vector<Target> Select(const std::vector<Source> &input, Func<Target, Source> func)
{
    std::vector<Target> result;
    
    for (Source x : input)
    {
        Target t = func(std::move(x));
        result.push_back(t);
    }
        

    return result;
}

TEST(LINQ, select)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Peter", 24)};
    auto result = Select<Ref<Person>, std::string>(persons, [](Ref<Person> x) -> std::string
                                                   { return x->name; });
}
