#include "Borg/String.h"
#include "IString.h"
#include <stdexcept>

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(std::string_view input) : m_Impl(IString::Create(input))
    {
    }

    String::String(std::wstring_view input) : m_Impl(IString::Create(input))
    {
    }

    // Copy constructor and assignment operator.
    String::String(const String &input)
    {
        throw std::exception("Not implemented");
    }

    String::String(Ref<IString> &&input): m_Impl(input)
    {}

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

    bool String::operator==(const String &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs.m_Impl) == 0;
    }

    bool String::operator==(std::string_view rhs) const noexcept
    {
        return *this == String(rhs);
    }

    bool String::operator==(std::wstring_view rhs) const noexcept
    {
        return *this == String(rhs);
    }

    String String::ToLower() const noexcept
    {
        return m_Impl->ToLower();
    }

    String String::ToUpper() const noexcept
    {
        return m_Impl->ToUpper();
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

    bool operator==(const std::string_view &lhs, const String &rhs)
    {
        return String(lhs) == rhs;
    }

    bool operator==(const std::wstring_view &lhs, const String &rhs)
    {
        return String(lhs) == rhs;
    }
}