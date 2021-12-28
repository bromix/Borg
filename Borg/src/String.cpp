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

    String::String(const char *input, std::size_t length) : m_Impl(IString::Create(std::string_view(input, length))) {}

    String::String(const wchar_t *input, std::size_t length) : m_Impl(IString::Create(std::wstring_view(input, length))) {}

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

    bool String::operator<(const String &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs.m_Impl) < 0;
    }

    bool String::operator>(const String &rhs) const noexcept
    {
        return m_Impl->CompareTo(rhs.m_Impl) > 0;
    }

    std::size_t String::Length() const
    {
        if (m_Impl == nullptr)
            throw NullReferenceException("Can not get the length of the string.");
        return m_Impl->Length();
    }

    String String::ToLower() const noexcept
    {
        return m_Impl->ToLower();
    }

    String String::ToUpper() const noexcept
    {
        return m_Impl->ToUpper();
    }

    String String::Insert(int startIndex, const String &value) const
    {
        return m_Impl->Insert(startIndex, value.m_Impl);
    }

    String String::Insert(int startIndex, const char *value) const
    {
        return m_Impl->Insert(startIndex, value);
    }

    String String::Insert(int startIndex, const wchar_t *&value) const
    {
        return m_Impl->Insert(startIndex, value);
    }

    String String::Insert(int startIndex, const std::string &value) const
    {
        return m_Impl->Insert(startIndex, value);
    }

    String String::Insert(int startIndex, const std::wstring &value) const
    {
        return m_Impl->Insert(startIndex, value);
    }

    String String::Append(const String &value) const
    {
        return Insert(Length(), value);
    }

    String String::Append(const char *value) const
    {
        return Insert(Length(), value);
    }

    String String::Append(const wchar_t *&value) const
    {
        return Insert(Length(), value);
    }

    String String::Append(const std::string &value) const
    {
        return Insert(Length(), value);
    }

    String String::Append(const std::wstring &value) const
    {
        return Insert(Length(), value);
    }

    String String::Prepend(const String &value) const
    {
        return Insert(0, value);
    }

    String String::Prepend(const char *value) const
    {
        return Insert(0, value);
    }

    String String::Prepend(const wchar_t *&value) const
    {
        return Insert(0, value);
    }

    String String::Prepend(const std::string &value) const
    {
        return Insert(0, value);
    }

    String String::Prepend(const std::wstring &value) const
    {
        return Insert(0, value);
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

    String String::operator+(const String &rhs) const noexcept
    {
        return Append(rhs);
    }

    String String::operator+(const char *rhs) const noexcept
    {
        return Append(rhs);
    }

    String String::operator+(const wchar_t *rhs) const noexcept
    {
        return Append(rhs);
    }

    String String::operator+(const std::string &rhs) const noexcept
    {
        return Append(rhs);
    }

    String String::operator+(const std::wstring &rhs) const noexcept
    {
        return Append(rhs);
    }

    String operator+(const char *lhs, const String &rhs)
    {
        return rhs.Prepend(lhs);
    }

    String operator+(const wchar_t *lhs, const String &rhs)
    {
        return rhs.Prepend(lhs);
    }

    String operator+(const std::string &lhs, const String &rhs)
    {
        return rhs.Prepend(lhs);
    }

    String operator+(const std::wstring &lhs, const String &rhs)
    {
        return rhs.Prepend(lhs);
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