#include "Borg/String.h"
#include "StringImpl.h"
#include <stdexcept>

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(std::string_view input)
    {
        m_Impl = String::Impl::Create(input);
    }

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

    bool String::IsNull() const
    {
        return m_Impl == nullptr;
    }
}