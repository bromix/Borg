#include "Borg/Exception.h"
#include "Utf16String.h"
#include "Windows.h"

namespace Borg
{
    Ref<String::IString> String::IString::Create(std::string_view input)
    {
        return CreateRef<Utf16String>(input);
    }

    Ref<String::IString> String::IString::Create(std::wstring_view input)
    {
        return CreateRef<Utf16String>(input);
    }

    Utf16String::Utf16String(std::string_view input)
    {
        if (input.empty())
            return;

        constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;
        auto utf16Length = ::MultiByteToWideChar(
            CP_UTF8,        // Source string is in UTF-8
            kFlags,         // Conversion flags
            input.data(),   // Source UTF-8 string pointer
            input.length(), // Length of the source UTF-8 string, in chars
            nullptr,        // Unused - no conversion done in this step
            0               // Request size of destination buffer, in wchar_ts
        );

        // FIXME: throw
        if (utf16Length == 0)
        {
            // Conversion error: capture error code and throw
            const DWORD error = ::GetLastError();
            // throw Utf8ConversionException(
            //     "Cannot get result string length when converting "
            //     "from UTF-8 to UTF-16 (MultiByteToWideChar failed).",
            //     error);
        }

        prepare(utf16Length);

        int result = ::MultiByteToWideChar(
            CP_UTF8,        // Source string is in UTF-8
            kFlags,         // Conversion flags
            input.data(),   // Source UTF-8 string pointer
            input.length(), // Length of source UTF-8 string, in chars
            m_Data,         // Pointer to destination buffer
            utf16Length     // Size of destination buffer, in wchar_ts
        );

        // FIXME: throw
        if (result == 0)
        {
            // Conversion error: capture error code and throw
            const DWORD error = ::GetLastError();
            // throw Utf8ConversionException(
            //     "Cannot convert from UTF-8 to UTF-16 "
            //     "(MultiByteToWideChar failed).",
            //     error);
        }
    }

    Utf16String::Utf16String(std::wstring_view input)
    {
        prepare(input.length());
        std::wmemcpy(m_Data, input.data(), input.length());
    }

    Utf16String::~Utf16String()
    {
        reset();
    }

    Ref<String::IString> Utf16String::CreateCopy() const
    {
        return CreateRef<Utf16String>(m_Data);
    }

    std::size_t Utf16String::Length() const
    {
        return m_Length;
    }

    Ref<String::IString> Utf16String::ToLower() const
    {
        Ref<Utf16String> copy = CreateRef<Utf16String>(m_Data);
        ::CharLowerW(copy->m_Data);
        return copy;
    }

    Ref<String::IString> Utf16String::ToUpper() const
    {
        Ref<Utf16String> copy = CreateRef<Utf16String>(m_Data);
        ::CharUpperW(copy->m_Data);
        return copy;
    }

    Ref<String::IString> Utf16String::Insert(int startIndex, const Ref<String::IString> &value) const
    {
        Ref<Utf16String> copy = CreateRef<Utf16String>(m_Data);
        return Insert(startIndex, copy->m_Data);
    }

    Ref<String::IString> Utf16String::Insert(int startIndex, std::string_view value) const
    {
        return Insert(startIndex, Utf16String(value).m_Data);
    }

    Ref<String::IString> Utf16String::Insert(int startIndex, std::wstring_view value) const
    {
        if (startIndex < 0 || startIndex >= m_Length)
            throw ArgumentOutOfRangeException("startIndex");

        // Construct String with an initialzed length.
        Ref<Utf16String> newString = CreateRef<Utf16String>(m_Length + value.length());

        wchar_t *targetData = newString->m_Data;
        wchar_t *sourceData = m_Data;

        if (startIndex > 0)
            std::wmemcpy(targetData, sourceData, startIndex);

        targetData += startIndex;
        std::wmemcpy(targetData, value.data(), value.length());

        targetData += value.length();
        sourceData += startIndex;
        std::wmemcpy(targetData, sourceData, m_Length - startIndex);

        return newString;
    }

    bool Utf16String::StartsWith(const Ref<IString> &text) const
    {
        Ref<Utf16String> other = std::dynamic_pointer_cast<Utf16String>(text);
        return StartsWith(other->m_Data);
    }

    bool Utf16String::StartsWith(std::string_view text) const
    {
        return StartsWith(Utf16String(text).m_Data);
    }

    bool Utf16String::StartsWith(std::wstring_view text) const
    {
        // TODO: check length
        auto result = wcsncmp(m_Data, text.data(), text.length());
        return result == 0;
    }

    bool Utf16String::EndsWith(const Ref<IString> &text) const
    {
        Ref<Utf16String> other = std::dynamic_pointer_cast<Utf16String>(text);
        return EndsWith(other->m_Data);
    }

    bool Utf16String::EndsWith(std::string_view text) const
    {
        return EndsWith(Utf16String(text).m_Data);
    }

    bool Utf16String::EndsWith(std::wstring_view text) const
    {
        // TODO: check length
        // move the pointer relative to the end.
        const wchar_t *ptr = m_Data + m_Length - text.length();
        auto result = wcsncmp(ptr, text.data(), text.length());
        return result == 0;
    }

    bool Utf16String::IsEmpty() const
    {
        return m_Length == 0;
    }

    int Utf16String::CompareTo(const Ref<IString> &rhs) const
    {
        Ref<Utf16String> other = std::dynamic_pointer_cast<Utf16String>(rhs);
        return CompareTo(other->m_Data);
    }

    int Utf16String::CompareTo(std::string_view rhs) const
    {
        return CompareTo(Utf16String(rhs).m_Data);
    }

    int Utf16String::CompareTo(std::wstring_view rhs) const
    {
        return std::wcscmp(m_Data, rhs.data());
    }

    Utf16String::Utf16String(std::size_t length)
    {
        prepare(length);
    }

    void Utf16String::reset()
    {
        if (m_Data == nullptr)
            return;

        delete[] m_Data;
        m_Data = nullptr;
        m_Length = 0;
    }

    void Utf16String::prepare(std::size_t length)
    {
        // TODO: check length (max)
        reset();
        m_Length = length;
        m_Data = new wchar_t[(m_Length + 1) * sizeof(wchar_t)];
        m_Data[m_Length] = '\0';
    }
}