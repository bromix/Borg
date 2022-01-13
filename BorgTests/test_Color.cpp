#include "Borg/Color.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(Color, FromArgb)
{
    Color color = Color::FromArgb(255, 255, 255);
    ASSERT_EQ(255, color.A());
    ASSERT_EQ(255, color.R());
    ASSERT_EQ(255, color.G());
    ASSERT_EQ(255, color.B());
}

TEST(Color, Blue)
{
    Color color = Color::FromArgb(0xFF0000FF);
    ASSERT_EQ(255, color.A());
    ASSERT_EQ(0, color.R());
    ASSERT_EQ(0, color.G());
    ASSERT_EQ(255, color.B());
}

TEST(Color, Black)
{
    Color color = Color::Black;
    ASSERT_EQ(255, color.A());
    ASSERT_EQ(0, color.R());
    ASSERT_EQ(0, color.G());
    ASSERT_EQ(0, color.B());
}