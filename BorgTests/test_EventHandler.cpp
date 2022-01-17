#include "Borg/Events.h"
#include <gtest/gtest.h>

class Timer
{
public:
    Timer() = default;
    Borg::Event<> Tick;
};

using namespace Borg;
TEST(EventHandler2, Blub)
{
    Timer tm;
    tm.Tick += []()
    {
        int x = 0;
    };

    tm.Tick.Call();
}
