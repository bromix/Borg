#include "Borg/DateTime.h"
#include <gtest/gtest.h>
#include <chrono>

using namespace Borg;
using namespace std;

TEST(DateTime, initial)
{
    auto now = chrono::system_clock::now();
    auto now_ms = chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch();
    auto seconds = chrono::duration_cast<std::chrono::seconds>(now_ms).count();
    auto millisecond = (int32_t)(now_ms.count() - (seconds * 1000));

    std::tm tm = {};
    gmtime_s(&tm, &seconds);
    auto x = 0;
}
