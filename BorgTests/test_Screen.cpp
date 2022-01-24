#include "Borg/Screen.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(Screen, Primary)
{
    auto primaryScreen = Screen::PrimaryScreen();
    ASSERT_TRUE(primaryScreen.IsPrimary());
}

TEST(Screen, AllScreens)
{
    auto allScreens = Screen::GetAllScreens();
}
