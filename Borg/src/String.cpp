#include "Borg/String.h"
#include <stdexcept>

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    // Copy constructor and assignment operator.
    String::String(const String &input)
    {
        throw std::exception("Not implemented");
    }

    String String::operator=(const String &input)
    {
        throw std::exception("Not implemented");
    }

    // Move constructor and assignment operator.
    String::String(String &&input)
    {
        throw std::exception("Not implemented");
    }

    String String::operator=(String &&input)
    {
        throw std::exception("Not implemented");
    }
}