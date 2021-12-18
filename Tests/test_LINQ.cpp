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

template <typename Source, typename F, typename Return = std::invoke_result<F, Source>::type>
auto Select(const std::vector<Source> &input, F func)
{
    std::vector<Return> result;

    for (Source x : input)
    {
        Return t = func(std::move(x));
        result.push_back(t);
    }

    return result;
}

template <typename T, typename F, typename R = typename std::result_of<F(T)>::type>
auto select(const std::vector<T> &c, F f)
{
    std::vector<R> v;
    std::transform(std::begin(c), std::end(c), std::back_inserter(v), f);
    return v;
}

TEST(LINQ, select)
{
    std::vector<Ref<Person>> persons = {
        CreateRef<Person>("Hans", 35),
        CreateRef<Person>("Peter", 24)};
    auto result = Select(
        persons, [](Ref<Person> x) -> auto { return x->age; });
}
