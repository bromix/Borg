#include "Borg/String.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(String, DefaultConstructor)
{
    String text;
    ASSERT_TRUE(text.IsNull());
    ASSERT_TRUE(text.IsEmpty());
    ASSERT_TRUE(text.IsNullOrEmpty());
}

TEST(String, NullConstructor)
{
    String text = nullptr;
    ASSERT_TRUE(text.IsNull());
    ASSERT_TRUE(text.IsEmpty());
    ASSERT_TRUE(text.IsNullOrEmpty());
}

TEST(String, EmptyString)
{
    String text = "";
    ASSERT_FALSE(text.IsNull());
    ASSERT_TRUE(text.IsEmpty());
}

TEST(String, Utf8String)
{
    String text = "Hello";
    ASSERT_FALSE(text.IsNullOrEmpty());
}

TEST(String, UnicodeString)
{
    String text = L"Hello";
    ASSERT_FALSE(text.IsNullOrEmpty());
}

TEST(String, Equals)
{
    String name = "Peter";
    ASSERT_EQ(name, "Peter");
    ASSERT_EQ(name, L"Peter");
    ASSERT_EQ("Peter", name);
    ASSERT_EQ(L"Peter", name);
    ASSERT_TRUE("Peter" == name);
    ASSERT_TRUE(name == "Peter");
}

TEST(String, ToLower)
{
    String name = "PEtEr";
    ASSERT_EQ(name.ToLower(), "peter");
}

TEST(String, ToUpper)
{
    String name = "PEtEr";
    ASSERT_EQ(name.ToUpper(), "PETER");
}

TEST(String, StartsWith)
{
    String test = L"Hello World";
    ASSERT_TRUE(test.StartsWith("Hello"));
    ASSERT_FALSE(test.StartsWith("World"));
}

TEST(String, EndsWith)
{
    String test = "Hello World";
    ASSERT_TRUE(test.EndsWith("World"));
    ASSERT_FALSE(test.EndsWith("Hello"));
}

TEST(String, Insert_0)
{
    String text = "World";
    String helloWorld = text.Insert(0, "Hello ");
    ASSERT_EQ("Hello World", helloWorld);
}

// TEST(String, Append)
// {
//     String world = " World";
//     String helloWorld = "Hello" + world;
//     ASSERT_EQ("Hello World", helloWorld);
// }