#include "Borg/Environment.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(Environment, MachineName)
{
    auto machineName = Environment::MachineName();
    ASSERT_FALSE(machineName.IsNullOrEmpty());
}

TEST(Environment, GetSpecialFolder_LocalApplicationData)
{
    auto path = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
    ASSERT_FALSE(path.IsNullOrEmpty());
}

TEST(Environment, GetSpecialFolder_ApplicationData)
{
    auto path = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);
    ASSERT_FALSE(path.IsNullOrEmpty());
}