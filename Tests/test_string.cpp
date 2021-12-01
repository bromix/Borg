#include "Borg/String.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(String, DefaultConstructor)
{
    String text;
    ASSERT_TRUE(text.IsNull());
    // ASSERT_TRUE(text.IsEmpty());
    // ASSERT_TRUE(text.IsNullOrEmpty());
}

TEST(String, NullConstructor)
{
    String text = nullptr;
    ASSERT_TRUE(text.IsNull());
    // ASSERT_TRUE(text.IsEmpty());
    // ASSERT_TRUE(text.IsNullOrEmpty());
}

TEST(String, UTF8Text)
{
    String text = "Hello";
    text.IsEmpty();
}