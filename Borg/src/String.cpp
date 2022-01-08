#include "Borg/String.h"
#include "Borg/Exception.h"
#include "Borg/Encoding.h"
#include "Borg/CharBuffer.h"

namespace Borg
{
    String::String() {}

    String::String(std::nullptr_t) {}

    String::String(const char *input) : String(input != nullptr ? CharBuffer::CopyFrom(input) : CharBuffer())
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const wchar_t *input) : String(input != nullptr ? WideCharBuffer::CopyFrom(input) : WideCharBuffer())
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const std::string &input) : String(CharBuffer::CopyFrom(input.c_str()))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const std::wstring &input) : String(WideCharBuffer::CopyFrom(input.c_str()))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const String &input) : m_Buffer(input.m_Buffer)
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const char *input, std::size_t length) : String(CharBuffer::CopyFrom(std::string_view(input, length)))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const wchar_t *input, std::size_t length) : String(WideCharBuffer::CopyFrom(std::wstring_view(input, length)))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const CharBuffer &input) : m_Buffer(Encoding::Convert<Encoding::Default>(input))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(CharBuffer &&input) : m_Buffer(Encoding::Convert<Encoding::Default>(std::move(input)))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(const WideCharBuffer &input) : m_Buffer(Encoding::Convert<Encoding::Default>(input))
    {
        m_Data = m_Buffer.Data();
    }

    String::String(WideCharBuffer &&input) : m_Buffer(Encoding::Convert<Encoding::Default>(std::move(input)))
    {
        m_Data = m_Buffer.Data();
    }

    String String::operator=(const String &input)
    {
        m_Buffer = Encoding::Default(input.GetBuffer());
        m_Data = m_Buffer.Data();
        return *this;
    }

    String::String(String &&input)
    {
        m_Buffer = nullptr;
        std::swap(m_Buffer, input.m_Buffer);
        m_Data = m_Buffer.Data();
    }

    String String::operator=(String &&input)
    {
        m_Buffer = nullptr;
        std::swap(m_Buffer, input.m_Buffer);
        m_Data = m_Buffer.Data();
        return *this;
    }

    bool String::operator==(const String &rhs) const
    {
        return m_Buffer.CompareTo(rhs.m_Buffer) == 0;
    }

    bool String::operator==(const char *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(rhs))) == 0;
    }

    bool String::operator==(const wchar_t *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(rhs))) == 0;
    }

    bool String::operator==(const std::string &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(rhs))) == 0;
    }

    bool String::operator==(const std::wstring &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(rhs))) == 0;
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
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(rhs))) < 0;
    }

    bool String::operator<(const wchar_t *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(rhs))) < 0;
    }

    bool String::operator<(const std::string &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(rhs))) < 0;
    }

    bool String::operator<(const std::wstring &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(rhs))) < 0;
    }

    bool String::operator>(const String &rhs) const
    {
        return m_Buffer.CompareTo(rhs.m_Buffer) > 0;
    }

    bool String::operator>(const char *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(rhs))) > 0;
    }

    bool String::operator>(const wchar_t *rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(rhs))) > 0;
    }

    bool String::operator>(const std::string &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(rhs))) > 0;
    }

    bool String::operator>(const std::wstring &rhs) const
    {
        return m_Buffer.CompareTo(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(rhs))) > 0;
    }

    String::operator bool() const
    {
        return !IsNullOrEmpty();
    }

    String::operator std::string() const
    {
        return std::string(Encoding::Convert<CharBuffer>(m_Buffer));
    }

    String::operator std::wstring() const
    {
        return std::wstring(Encoding::Convert<WideCharBuffer>(m_Buffer));
    }

    Encoding::Default String::GetBuffer() const
    {
        // Always return a copy of the buffer.
        return Encoding::Default(m_Buffer);
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
        return String(std::move(m_Buffer.ToUpper()));
    }

    String String::Insert(int startIndex, const String &value) const
    {
        if (value.IsNull())
            throw ArgumentNullException("value");

        return String(m_Buffer.Insert(startIndex, Encoding::Convert<Encoding::Default>(value)));
    }

    String String::Insert(int startIndex, const char *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

        return String(m_Buffer.Insert(startIndex, Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(value))));
    }

    String String::Insert(int startIndex, const wchar_t *value) const
    {
        if (value == nullptr)
            throw ArgumentNullException("value");

        return String(m_Buffer.Insert(startIndex, Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(value))));
    }

    String String::Insert(int startIndex, const std::string &value) const
    {
        return String(m_Buffer.Insert(startIndex, Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(value))));
    }

    String String::Insert(int startIndex, const std::wstring &value) const
    {
        return String(m_Buffer.Insert(startIndex, Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(value))));
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

        return m_Buffer.StartsWith(Encoding::Convert<Encoding::Default>(text));
    }

    bool String::StartsWith(const char *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.StartsWith(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(text)));
    }

    bool String::StartsWith(const wchar_t *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.StartsWith(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(text)));
    }

    bool String::StartsWith(const std::string &text) const
    {
        return m_Buffer.StartsWith(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(text)));
    }

    bool String::StartsWith(const std::wstring &text) const
    {
        return m_Buffer.StartsWith(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(text)));
    }

    bool String::EndsWith(const String &text) const
    {
        if (text.IsNull())
            throw ArgumentNullException("text");

        return m_Buffer.EndsWith(Encoding::Convert<Encoding::Default>(text));
    }

    bool String::EndsWith(const char *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.EndsWith(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(text)));
    }

    bool String::EndsWith(const wchar_t *text) const
    {
        if (text == nullptr)
            throw ArgumentNullException("text");

        return m_Buffer.EndsWith(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(text)));
    }

    bool String::EndsWith(const std::string &text) const
    {
        return m_Buffer.EndsWith(Encoding::Convert<Encoding::Default>(CharBuffer::ViewFrom(text)));
    }

    bool String::EndsWith(const std::wstring &text) const
    {
        return m_Buffer.EndsWith(Encoding::Convert<Encoding::Default>(WideCharBuffer::ViewFrom(text)));
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

    String String::operator+=(const String &rhs)
    {
        auto newString = Append(rhs);
        *this = std::move(newString);
        return *this;
    }

    String String::operator+=(const char *rhs)
    {
        auto newString = Append(rhs);
        *this = std::move(newString);
        return *this;
    }

    String String::operator+=(const wchar_t *rhs)
    {
        auto newString = Append(rhs);
        *this = std::move(newString);
        return *this;
    }

    String String::operator+=(const std::string &rhs)
    {
        auto newString = Append(rhs);
        *this = std::move(newString);
        return *this;
    }

    String String::operator+=(const std::wstring &rhs)
    {
        auto newString = Append(rhs);
        *this = std::move(newString);
        return *this;
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