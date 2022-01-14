#include "Borg/Drawing/Point.h"
#include <gtest/gtest.h>

using namespace Borg::Drawing;

TEST(DrawingPoint, Constructor)
{
    Point point = Point(100, 200);
    ASSERT_EQ(100, point.X);
    ASSERT_EQ(200, point.Y);
}

TEST(DrawingPoint, Equal)
{
    Point pointA = Point(100, 200);
    Point pointB = Point(100, 200);
    ASSERT_EQ(pointA, pointB);
}

TEST(DrawingPoint, NotEqual)
{
    Point pointA = Point(100, 200);
    Point pointB = Point(200, 200);
    ASSERT_NE(pointA, pointB);
}
