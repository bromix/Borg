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
    // ASSERT_EQ("Peter", name);
    // ASSERT_TRUE("Peter" == name);
    // ASSERT_TRUE(name == "Peter");
}