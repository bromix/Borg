#include "Borg/LINQ.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace Borg;

struct Person
{
    String Name;
    int Age;
};

struct Pet
{
    String Name;
    int Age;
};

TEST(LINQ, FromVector)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers);
    auto vec = result.ToVector();
}

TEST(LINQ, First)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers).First();
    ASSERT_EQ(1, result);
}

TEST(LINQ, FirstWithPredicate)
{
    std::vector<int> numbers = {9, 34, 65, 92, 87, 435, 3, 54, 83, 23, 87, 435, 67, 12, 19};
    auto result = LINQ::From(numbers).First([](int x)
                                            { return x > 80; });
    ASSERT_EQ(92, result);
}

TEST(LINQ, Last)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers).Last();
    ASSERT_EQ(10, result);
}

TEST(LINQ, LastWithPredicate)
{
    std::vector<int> numbers = {9, 34, 65, 92, 87, 435, 3, 54, 83, 23, 87, 67, 12, 19};
    auto result = LINQ::From(numbers).Last([](int x)
                                           { return x > 80; });
    ASSERT_EQ(87, result);
}

TEST(LINQ, Count)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers).Count();
    ASSERT_EQ(10, result);
}

TEST(LINQ, CountWithPredicate)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = LINQ::From(numbers).Count([](int x)
                                            { return x % 2 == 0; });
    ASSERT_EQ(5, result);
}

TEST(LINQ, Where)
{
    auto result = LINQ::From({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
                      .Where([](int x) -> bool
                             { return x > 5; })
                      .Where([](int x) -> bool
                             { return x % 2 == 0; })
                      .ToVector();

    ASSERT_EQ(3, result.size());
    ASSERT_EQ(6, result[0]);
    ASSERT_EQ(8, result[1]);
    ASSERT_EQ(10, result[2]);
}

TEST(LINQ, All)
{
    std::vector<Pet> pets = {
        {"Barley", 0},
        {"Boots", 4},
        {"Whiskers", 6}};

    auto result = LINQ::From(pets)
                      .All([](const Pet &pet)
                           { return pet.Name.StartsWith("B"); });

    ASSERT_FALSE(result);
}

// TEST(LINQ, OrderBy)
// {
//     std::vector<Ref<Person>> persons = {
//         CreateRef<Person>("Hans", 35),
//         CreateRef<Person>("Detlef", 35),
//         CreateRef<Person>("Adam", 24)};
//     auto result = LINQ::From(persons)
//                       .OrderBy([](Ref<Person> x)
//                                { return x->name; })
//                       .ToVector();
// }

// TEST(LINQ, OrderByDescending)
// {
//     std::vector<Ref<Person>> persons = {
//         CreateRef<Person>("Hans", 35),
//         CreateRef<Person>("Detlef", 35),
//         CreateRef<Person>("Adam", 24)};
//     auto result = LINQ::From(persons)
//                       .OrderByDescending([](Ref<Person> x)
//                                          { return x->name; })
//                       .ToVector();
// }

// TEST(LINQ, OrderByThenBy)
// {
//     std::vector<std::string> fruits = {"grape", "passionfruit", "banana", "mango", "orange", "raspberry", "apple", "blueberry"};
//     auto result = LINQ::From(fruits)
//                       .OrderBy([](const std::string value)
//                                { return value.length(); })
//                       .ThenBy([](const std::string value)
//                               { return value; })
//                       .ToVector();

//     /*
//     This code produces the following output:

//     apple
//     grape
//     mango
//     banana
//     orange
//     blueberry
//     raspberry
//     passionfruit
// */
// }

TEST(LINQ, select)
{
    std::vector<Person> persons = {
        {"Hans", 35},
        {"Peter", 24}};

    auto result = LINQ::From(persons)
                      .Select([](const Person &x)
                              { return x.Age; })
                      .ToVector();
    ASSERT_EQ(2, result.size());
    ASSERT_EQ(35, result[0]);
    ASSERT_EQ(24, result[1]);
}

TEST(LINQ, WhereAndSelect)
{
    std::vector<Person> persons = {
        {"Hans", 35},
        {"Peter", 24}};

    auto result = LINQ::From(persons)
                      .Where([](const Person &x)
                             { return x.Name == "Hans"; })
                      .Select([](const Person &x)
                              { return x.Age; })
                      .ToVector();
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(35, result[0]);
}