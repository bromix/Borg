#include "Borg/String.h"
#include "Borg/Exception.h"
#include "IString.h"

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(const char *input) : m_Impl(IString::Create(input)) {}

    String::String(const wchar_t *input) : m_Impl(IString::Create(input)) {}

    String::String(const std::string &input) : m_Impl(IString::Create(input)) {}

    String::String(const std::wstring &input) : m_Impl(IString::Create(input)) {}

    String::String(const String &input) : m_Impl(input.m_Impl->CreateCopy()) {}

    String::String(Ref<IString> &&input) : m_Impl(std::move(input)) {}

    String String::operator=(const String &input)
    {
        m_Impl = input.m_Impl->CreateCopy();
        return *this;
    }

    // Move constructor and assignment operator.
    String::String(String &&input)
    {
        m_Impl = nullptr;
        std::swap(m_Impl, input.m_Impl);
    }

    String String::operator=(String &&input)
    {
        m_Impl = nullptr;
        std::swap(m_Impl, input.m_Impl);
        return *this;
    }

    bool String::operator==(const String &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs.m_Impl) == 0;
    }

    bool String::operator==(const char *rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs) == 0;
    }

    bool String::operator==(const wchar_t *rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs) == 0;
    }

    bool String::operator==(const std::string &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs) == 0;
    }

    bool String::operator==(const std::wstring &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs) == 0;
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

    bool String::StartsWith(const char *text) const noexcept
    {
        return m_Impl->StartsWith(text);
    }

    bool String::StartsWith(const wchar_t *&text) const noexcept
    {
        return m_Impl->StartsWith(text);
    }

    bool String::StartsWith(const std::string &text) const noexcept
    {
        return m_Impl->StartsWith(text);
    }

    bool String::StartsWith(const std::wstring &text) const noexcept
    {
        return m_Impl->StartsWith(text);
    }

    bool String::EndsWith(const String &text) const noexcept
    {
        return m_Impl->EndsWith(text.m_Impl);
    }

    bool String::EndsWith(const char *text) const noexcept
    {
        return m_Impl->EndsWith(text);
    }

    bool String::EndsWith(const wchar_t *&text) const noexcept
    {
        return m_Impl->EndsWith(text);
    }

    bool String::EndsWith(const std::string &text) const noexcept
    {
        return m_Impl->EndsWith(text);
    }

    bool String::EndsWith(const std::wstring &text) const noexcept
    {
        return m_Impl->EndsWith(text);
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

    String operator+(const char *lhs, const String &rhs)
    {
        throw NotImplementedException();
    }

    String operator+(const wchar_t *lhs, const String &rhs)
    {
        throw NotImplementedException();
    }

    String operator+(const std::string &lhs, const String &rhs)
    {
        throw NotImplementedException();
    }

    String operator+(const std::wstring &lhs, const String &rhs)
    {
        throw NotImplementedException();
    }

    bool operator==(const char *lhs, const String &rhs)
    {
        return rhs == lhs;
    }

    bool operator==(const wchar_t *lhs, const String &rhs)
    {
        return rhs == lhs;
    }

    bool operator==(const std::string &lhs, const String &rhs)
    {
        return rhs == lhs;
    }

    bool operator==(const std::wstring &lhs, const String &rhs)
    {
        return rhs == lhs;
    }
}