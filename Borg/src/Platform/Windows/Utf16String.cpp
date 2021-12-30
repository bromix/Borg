#include "Borg/RefCast.h"
#include "Utf16String.h"
#include "StringConversion.h"
#include "Windows.h"

namespace Borg
{
    Ref<IString> IString::Create(std::string_view input)
    {
        return CreateRef<Utf16String>(input);
    }

    Ref<IString> IString::Create(std::wstring_view input)
    {
        return CreateRef<Utf16String>(input);
    }

    Utf16String::Utf16String(std::string_view input)
    {
        m_StringBuffer = ToUtf16(input);
    }

    Utf16String::Utf16String(std::wstring_view input)
    {
        prepare(input.length());
        m_StringBuffer.CopyFrom(input);
    }

    Utf16String::Utf16String(const WideCharBuffer &buffer) : m_StringBuffer(buffer)
    {
    }

    Utf16String::~Utf16String()
    {
    }

    Ref<IString> Utf16String::CreateCopy() const
    {
        return CreateRef<Utf16String>(m_StringBuffer);
    }

    std::size_t Utf16String::Length() const
    {
        return m_StringBuffer.Count();
    }

    Ref<IString> Utf16String::ToLower() const
    {
        Ref<Utf16String> copy = CreateRef<Utf16String>(m_StringBuffer);
        ::CharLowerW(copy->m_StringBuffer);
        return copy;
    }

    Ref<IString> Utf16String::ToUpper() const
    {
        Ref<Utf16String> copy = CreateRef<Utf16String>(m_StringBuffer);
        ::CharUpperW(copy->m_StringBuffer);
        return copy;
    }

    Ref<IString> Utf16String::Insert(int startIndex, const Ref<IString> &value) const
    {
        Ref<Utf16String> copy = CreateRef<Utf16String>(m_StringBuffer);
        return Insert(startIndex, copy->m_StringBuffer);
    }

    Ref<IString> Utf16String::Insert(int startIndex, std::string_view value) const
    {
        return Insert(startIndex, Utf16String(value).m_StringBuffer);
    }

    Ref<IString> Utf16String::Insert(int startIndex, std::wstring_view value) const
    {
        if (startIndex < 0 || startIndex > m_StringBuffer.Count())
            throw ArgumentOutOfRangeException("startIndex");

        Ref<Utf16String> newString = CreateRef<Utf16String>(m_StringBuffer.Count() + value.length());

        wchar_t *targetData = newString->m_StringBuffer;
        wchar_t *sourceData = m_StringBuffer;

        if (startIndex > 0)
            std::wmemcpy(targetData, sourceData, startIndex);

        targetData += startIndex;
        std::wmemcpy(targetData, value.data(), value.length());

        targetData += value.length();
        sourceData += startIndex;
        std::wmemcpy(targetData, sourceData, m_StringBuffer.Count() - startIndex);

        return newString;
    }

    bool Utf16String::StartsWith(const Ref<IString> &text) const
    {
        Ref<Utf16String> other = RefCast<Utf16String>(text);
        return StartsWith(other->m_StringBuffer);
    }

    bool Utf16String::StartsWith(std::string_view text) const
    {
        return StartsWith(Utf16String(text).m_StringBuffer);
    }

    bool Utf16String::StartsWith(std::wstring_view text) const
    {
        if(text.length() > m_StringBuffer.Count())
            return false;
        auto result = wcsncmp(m_StringBuffer, text.data(), text.length());
        return result == 0;
    }

    bool Utf16String::EndsWith(const Ref<IString> &text) const
    {
        Ref<Utf16String> other = RefCast<Utf16String>(text);
        return EndsWith(other->m_StringBuffer);
    }

    bool Utf16String::EndsWith(std::string_view text) const
    {
        return EndsWith(Utf16String(text).m_StringBuffer);
    }

    bool Utf16String::EndsWith(std::wstring_view text) const
    {
        if (text.length() > m_StringBuffer.Count())
            return false;

        // We must subtract the null-termination '\0'
        auto ptr = &m_StringBuffer[m_StringBuffer.Count() - text.length()];
        auto result = wcsncmp(ptr, text.data(), text.length());
        return result == 0;
    }

    bool Utf16String::IsEmpty() const
    {
        return m_StringBuffer.Count() == 0;
    }

    int Utf16String::CompareTo(const Ref<IString> &rhs) const
    {
        Ref<Utf16String> other = RefCast<Utf16String>(rhs);
        return CompareTo(other->m_StringBuffer);
    }

    int Utf16String::CompareTo(std::string_view rhs) const
    {
        return CompareTo(Utf16String(rhs).m_StringBuffer);
    }

    int Utf16String::CompareTo(std::wstring_view rhs) const
    {
        return std::wcscmp(m_StringBuffer, rhs.data());
    }

    Utf16String::operator std::string() const
    {
        return ToUtf8(m_StringBuffer);
    }

    Utf16String::operator std::wstring() const
    {
        return m_StringBuffer;
    }

    Ref<IStringBuffer> Utf16String::GetBuffer() const
    {
        // Create a copy if this buffer.
        return CreateRef<WideCharBuffer>(m_StringBuffer);
    }

    Utf16String::Utf16String(std::size_t length)
    {
        prepare(length);
    }

    void Utf16String::prepare(std::size_t count)
    {
        m_StringBuffer = WideCharBuffer(count);
    }
}