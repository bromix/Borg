#include "Borg/String.h"
#include "IString.h"
#include <stdexcept>

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(const char *input) : m_Impl(IString::Create(input))
    {
    }

    String::String(const wchar_t *input) : m_Impl(IString::Create(input))
    {
    }

    // Copy constructor and assignment operator.
    String::String(const String &input)
    {
        throw std::exception("Not implemented");
    }

    String::String(Ref<IString> &&input) : m_Impl(input)
    {
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

    bool String::operator==(const char* rhs) const noexcept
    {
        return *this == String(rhs);
    }
    
    bool String::operator==(const wchar_t* rhs) const noexcept
    {
        return *this == String(rhs);
    }

    bool String::operator==(const String &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs.m_Impl) == 0;
    }

    String String::ToLower() const noexcept
    {
        return m_Impl->ToLower();
    }

    String String::ToUpper() const noexcept
    {
        return m_Impl->ToUpper();
    }

    bool String::StartsWith(const String &text) const noexcept
    {
        return m_Impl->StartsWith(text.m_Impl);
    }

    bool String::EndsWith(const String &text) const noexcept
    {
        return m_Impl->EndsWith(text.m_Impl);
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

    bool String::IsNullOrEmpty() const noexcept
    {
        return IsNull() || IsEmpty();
    }

    bool operator==(const char* lhs, const String &rhs)
    {
        return String(lhs) == rhs;
    }

    bool operator==(const wchar_t* lhs, const String &rhs)
    {
        return String(lhs) == rhs;
    }
}