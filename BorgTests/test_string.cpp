#include "Borg/String.h"
#include "Borg/StringBuffer.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(String, DefaultConstructor)
{
    String text;
    ASSERT_TRUE(text.IsNull());
    ASSERT_TRUE(text.IsEmpty());
    ASSERT_TRUE(text.IsNullOrEmpty());
    ASSERT_FALSE(text);
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
    ASSERT_EQ(11, helloWorld.Length());
}

TEST(String, Insert_5)
{
    String text = "Hello World";
    String helloNewWorld = text.Insert(5, " New");
    ASSERT_EQ("Hello New World", helloNewWorld);
    ASSERT_EQ(15, helloNewWorld.Length());
}

TEST(String, Insert_End)
{
    String text = "Hello";
    String helloWorld = text.Insert(5, " World");
    ASSERT_EQ("Hello World", helloWorld);
    ASSERT_EQ(11, helloWorld.Length());
}

TEST(String, Append)
{
    String hello = "Hello";
    String helloWorld = hello.Append(" World");
    ASSERT_EQ("Hello World", helloWorld);
    ASSERT_EQ(11, helloWorld.Length());
}

TEST(String, Prepend)
{
    String world = "World";
    String helloWorld = world.Prepend("Hello ");
    ASSERT_EQ("Hello World", helloWorld);
    ASSERT_EQ(11, helloWorld.Length());
}

TEST(String, PlusOperator)
{
    String world = "World";
    String helloWorld = "Hello " + world;
    ASSERT_EQ("Hello World", helloWorld);
    ASSERT_EQ(11, helloWorld.Length());
}

TEST(String, MultiPlusOperator)
{
    String text = "New";
    String helloNewWorld = "Hello " + text + " World";
    ASSERT_EQ("Hello New World", helloNewWorld);
    ASSERT_EQ(15, helloNewWorld.Length());
}

TEST(String, toWString)
{
    String hello = "Hello";
    std::wstring stdWString = hello;
    ASSERT_EQ(stdWString, hello);
}

TEST(String, toString)
{
    String hello = "Hello";
    std::string stdString = hello;
    ASSERT_EQ(stdString, hello);
}

TEST(String, GetBytes)
{
    String hello = "Hello";
    auto bytes = hello.GetBuffer<WideCharBuffer>();
}