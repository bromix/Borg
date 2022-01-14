#include "Borg/Drawing/Size.h"
#include <gtest/gtest.h>

using namespace Borg::Drawing;

TEST(DrawingSize, Constructor)
{
    Size size = Size(100, 200);
    ASSERT_EQ(100, size.Width);
    ASSERT_EQ(200, size.Height);
}

TEST(DrawingSize, Equal)
{
    Size sizeA = Size(100, 200);
    Size sizeB = Size(100, 200);
    ASSERT_EQ(sizeA, sizeB);
}

TEST(DrawingSize, NotEqual)
{
    Size sizeA = Size(100, 200);
    Size sizeB = Size(200, 200);
    ASSERT_NE(sizeA, sizeB);
}
