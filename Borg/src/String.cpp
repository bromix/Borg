#include "Borg/String.h"
#include "IString.h"
#include <stdexcept>

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(std::string_view input)
    {
        m_Impl = String::IString::Create(input);
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

    bool String::IsNull() const noexcept
    {
        return m_Impl == nullptr;
    }

    bool String::IsEmpty() const noexcept
    {
        if (m_Impl)
            return m_Impl->IsEmpty();
        return true;
    }
}