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
    Pet(const String &name, int age) : Name(name), Age(age) {}
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
        {"Barley", 8},
        {"Boots", 4},
        {"Whiskers", 6}};

    auto result = LINQ::From(pets)
                      .All([](const Pet &pet)
                           { return pet.Name.StartsWith("B"); });

    ASSERT_FALSE(result);
}

TEST(LINQ, OrderBy)
{
    std::vector<Ref<Pet>> pets = {
        CreateRef<Pet>("Barley", 8),
        CreateRef<Pet>("Boots", 4),
        CreateRef<Pet>("Whiskers", 1)};

    auto result = LINQ::From(pets)
                      .OrderBy([](const auto &pet)
                               { return pet->Age; })
                      .ToVector();

    ASSERT_EQ(1, result[0]->Age);
    ASSERT_EQ(4, result[1]->Age);
    ASSERT_EQ(8, result[2]->Age);
}

TEST(LINQ, OrderByDescending)
{
    auto result = LINQ::From({62, 83, 5, 13, 63, 97})
                      .OrderByDescending([](auto x)
                                         { return x; })
                      .ToVector();

    ASSERT_EQ(97, result[0]);
    ASSERT_EQ(83, result[1]);
    ASSERT_EQ(63, result[2]);
    ASSERT_EQ(62, result[3]);
    ASSERT_EQ(13, result[4]);
    ASSERT_EQ(5, result[5]);
}

TEST(LINQ, OrderByThenBy)
{
    std::vector<String> fruits = {"grape", "passionfruit", "banana", "mango", "orange", "raspberry", "apple", "blueberry"};
    auto result = LINQ::From(fruits)
                      .OrderBy([](const auto &value)
                               { return value.Length(); })
                      .ThenBy([](const auto &value)
                              { return value; })
                      .ToVector();

    ASSERT_EQ("apple", result[0]);
    ASSERT_EQ("grape", result[1]);
    ASSERT_EQ("mango", result[2]);
    ASSERT_EQ("banana", result[3]);
    ASSERT_EQ("orange", result[4]);
    ASSERT_EQ("blueberry", result[5]);
    ASSERT_EQ("raspberry", result[6]);
    ASSERT_EQ("passionfruit", result[7]);
}

TEST(LINQ, OrderByThenByDescending)
{
    std::vector<String> fruits = {"grape", "passionfruit", "banana", "mango", "orange", "raspberry", "apple", "blueberry"};
    auto result = LINQ::From(fruits)
                      .OrderBy([](const auto &value)
                               { return value.Length(); })
                      .ThenByDescending([](const auto &value)
                                        { return value; })
                      .ToVector();

    ASSERT_EQ("mango", result[0]);
    ASSERT_EQ("grape", result[1]);
    ASSERT_EQ("apple", result[2]);
    ASSERT_EQ("orange", result[3]);
    ASSERT_EQ("banana", result[4]);
    ASSERT_EQ("raspberry", result[5]);
    ASSERT_EQ("blueberry", result[6]);
    ASSERT_EQ("passionfruit", result[7]);
}

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