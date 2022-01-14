#include "Borg/Drawing/Rectangle.h"
#include <gtest/gtest.h>

using namespace Borg::Drawing;

TEST(DrawingRectangle, Constructor)
{
    Rectangle rc = Rectangle(10, 20, 100, 200);
    ASSERT_EQ(10, rc.X);
    ASSERT_EQ(20, rc.Y);
    ASSERT_EQ(100, rc.Width);
    ASSERT_EQ(200, rc.Height);
}

TEST(DrawingRectangle, Equal)
{
    Rectangle rcA = Rectangle(10, 20, 100, 200);
    Rectangle rcB = Rectangle(10, 20, 100, 200);
    ASSERT_EQ(rcA, rcB);
}

TEST(DrawingRectangle, NotEqual)
{
    Rectangle rcA = Rectangle(10, 20, 100, 200);
    Rectangle rcB = Rectangle(11, 20, 100, 200);
    ASSERT_NE(rcA, rcB);
}

TEST(DrawingRectangle, GetLocation)
{
    Rectangle rc = Rectangle(10, 20, 100, 200);
    Point pt = rc.GetLocation();
    ASSERT_EQ(10, pt.X);
    ASSERT_EQ(20, pt.Y);
}

TEST(DrawingRectangle, GetSize)
{
    Rectangle rc = Rectangle(10, 20, 100, 200);
    Size sz = rc.GetSize();
    ASSERT_EQ(100, sz.Width);
    ASSERT_EQ(200, sz.Height);
}
