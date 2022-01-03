#include "Borg/String.h"
#include "Borg/Exception.h"
#include "Borg/Encoding.h"
#include "Borg/CharBuffer.h"

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(const char *input) : m_Buffer(Encoding::ConvertTo<Encoding::Default, CharBuffer>(input)) {}

    String::String(const wchar_t *input) : m_Buffer(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(input)) {}

    String::String(const std::string &input) : m_Buffer(Encoding::ConvertTo<Encoding::Default, CharBuffer>(input)) {}

    String::String(const std::wstring &input) : m_Buffer(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(input)) {}

    String::String(const String &input) : m_Buffer(Encoding::ConvertTo<Encoding::Default>(input)) {}

    String::String(const char *input, std::size_t length) : m_Buffer(Encoding::ConvertTo<Encoding::Default, CharBuffer>(std::string_view(input, length))) {}

    String::String(const wchar_t *input, std::size_t length) : m_Buffer(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(std::wstring_view(input, length))) {}

    String::String(const WideCharBuffer &input):m_Buffer(Encoding::ConvertTo<Encoding::Default>(input)) {}
    
    String::String(WideCharBuffer &&input):m_Buffer(Encoding::ConvertTo<Encoding::Default>(std::move(input))) {}

    String String::operator=(const String &input)
    {
        m_Buffer = input ? Encoding::ConvertTo<Encoding::Default>(input) : nullptr;
        return *this;
    }

    // Move constructor and assignment operator.
    String::String(String &&input)
    {
        m_Buffer = nullptr;
        std::swap(m_Buffer, input.m_Buffer);
    }

    String String::operator=(String &&input)
    {
        m_Buffer = nullptr;
        std::swap(m_Buffer, input.m_Buffer);
        return *this;
    }

    bool String::operator==(const String &rhs) const
    {
        return m_Buffer.CompareTo(rhs.m_Buffer) == 0;
    }

    bool String::operator==(const char *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, CharBuffer>(rhs)) == 0;
    }

    bool String::operator==(const wchar_t *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(rhs)) == 0;
    }

    bool String::operator==(const std::string &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, CharBuffer>(rhs)) == 0;
    }

    bool String::operator==(const std::wstring &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(rhs)) == 0;
    }

    bool String::operator!=(const String &rhs) const
    {
        return !(*this == rhs);
    }

    bool String::operator!=(const char *rhs) const
    {
        return !(*this == rhs);
    }

    bool String::operator!=(const wchar_t *rhs) const
    {
        return !(*this == rhs);
    }

    bool String::operator!=(const std::string &rhs) const
    {
        return !(*this == rhs);
    }

    bool String::operator!=(const std::wstring &rhs) const
    {
        return !(*this == rhs);
    }

    bool String::operator<(const String &rhs) const
    {
        return m_Buffer.CompareTo(rhs.m_Buffer) < 0;
    }

    bool String::operator<(const char *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, CharBuffer>(rhs)) < 0;
    }

    bool String::operator<(const wchar_t *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(rhs)) < 0;
    }

    bool String::operator<(const std::string &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, CharBuffer>(rhs)) < 0;
    }

    bool String::operator<(const std::wstring &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(rhs)) < 0;
    }

    bool String::operator>(const String &rhs) const
    {
        return m_Buffer.CompareTo(rhs.m_Buffer) > 0;
    }

    bool String::operator>(const char *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, CharBuffer>(rhs)) > 0;
    }

    bool String::operator>(const wchar_t *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(rhs)) > 0;
    }

    bool String::operator>(const std::string &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, CharBuffer>(rhs)) > 0;
    }

    bool String::operator>(const std::wstring &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(rhs)) > 0;
    }

    String::operator bool() const
    {
        return !IsNullOrEmpty();
    }

    String::operator std::string() const
    {
        return "";
    }

    String::operator std::wstring() const
    {
        return L"";
    }

    Encoding::Default String::GetBuffer() const
    {
        return m_Buffer;
    }

    std::size_t String::Length() const
    {
        return m_Buffer.Length();
    }

    String String::ToLower() const noexcept
    {
        return String(std::move(m_Buffer.ToLower()));
    }

    String String::ToUpper() const noexcept
    {
        return String(m_Buffer.ToUpper());
    }

    String String::Insert(int startIndex, const String &value) const
    {
        if (value.IsNull())
            throw ArgumentNullException("value");

        return String(m_Buffer.Insert(startIndex, Encoding::ConvertTo<Encoding::Default>(value)));
    }

    String String::Insert(int startIndex, const char *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

        return String(m_Buffer.Insert(startIndex, Encoding::ConvertTo<Encoding::Default, CharBuffer>(value)));
    }

    String String::Insert(int startIndex, const wchar_t *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

        return String(m_Buffer.Insert(startIndex, Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(value)));
    }

    String String::Insert(int startIndex, const std::string &value) const
    {
        return String(m_Buffer.Insert(startIndex, Encoding::ConvertTo<Encoding::Default, CharBuffer>(value)));
    }

    String String::Insert(int startIndex, const std::wstring &value) const
    {
        return String(m_Buffer.Insert(startIndex, Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(value)));
    }

    String String::Append(const String &value) const
    {
        if (value.IsNull())
            throw ArgumentNullException("value");

        return Insert(Length(), value);
    }

    String String::Append(const char *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

        return Insert(Length(), value);
    }

    String String::Append(const wchar_t *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

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
        if (value.IsNull())
            throw ArgumentNullException("value");

        return Insert(0, value);
    }

    String String::Prepend(const char *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

        return Insert(0, value);
    }

    String String::Prepend(const wchar_t *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

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

    bool String::StartsWith(const String &text) const
    {
        if (text.IsNull())
            throw ArgumentNullException("text");

        return m_Buffer.StartsWith(Encoding::ConvertTo<Encoding::Default>(text));
    }

    bool String::StartsWith(const char *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.StartsWith(Encoding::ConvertTo<Encoding::Default, CharBuffer>(text));
    }

    bool String::StartsWith(const wchar_t *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.StartsWith(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(text));
    }

    bool String::StartsWith(const std::string &text) const
    {
        return m_Buffer.StartsWith(Encoding::ConvertTo<Encoding::Default, CharBuffer>(text));
    }

    bool String::StartsWith(const std::wstring &text) const
    {
        return m_Buffer.StartsWith(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(text));
    }

    bool String::EndsWith(const String &text) const
    {
        if (text.IsNull())
            throw ArgumentNullException("text");

        return m_Buffer.EndsWith(Encoding::ConvertTo<Encoding::Default>(text));
    }

    bool String::EndsWith(const char *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.EndsWith(Encoding::ConvertTo<Encoding::Default, CharBuffer>(text));
    }

    bool String::EndsWith(const wchar_t *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.EndsWith(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(text));
    }

    bool String::EndsWith(const std::string &text) const
    {
        return m_Buffer.EndsWith(Encoding::ConvertTo<Encoding::Default, CharBuffer>(text));
    }

    bool String::EndsWith(const std::wstring &text) const
    {
        return m_Buffer.EndsWith(Encoding::ConvertTo<Encoding::Default, WideCharBuffer>(text));
    }

    bool String::IsNull() const noexcept
    {
        return m_Buffer.IsNull();
    }

    bool String::IsEmpty() const noexcept
    {
        return m_Buffer.IsEmpty();
    }

    bool String::IsNullOrEmpty() const noexcept
    {
        return IsNull() || IsEmpty();
    }

    String String::operator+(const String &rhs) const
    {
        return Append(rhs);
    }

    String String::operator+(const char *rhs) const
    {
        return Append(rhs);
    }

    String String::operator+(const wchar_t *rhs) const
    {
        return Append(rhs);
    }

    String String::operator+(const std::string &rhs) const
    {
        return Append(rhs);
    }

    String String::operator+(const std::wstring &rhs) const
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

    bool operator!=(const char *lhs, const String &rhs)
    {
        return rhs != lhs;
    }

    bool operator!=(const wchar_t *lhs, const String &rhs)
    {
        return rhs != lhs;
    }

    bool operator!=(const std::string &lhs, const String &rhs)
    {
        return rhs != lhs;
    }

    bool operator!=(const std::wstring &lhs, const String &rhs)
    {
        return rhs != lhs;
    }
}