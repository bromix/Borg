#include "Utf16String.h"

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
    }

    Utf16String::Utf16String(std::wstring_view input)
    {
        init(input.size());
        memcpy(static_cast<void *>(m_Data), input.data(), m_Length * sizeof(wchar_t));
    }

    Utf16String::~Utf16String()
    {
        cleanup();
    }

    bool Utf16String::IsEmpty() const
    {
        return m_Length == 0;
    }

    void Utf16String::cleanup()
    {
        if (m_Data == nullptr)
            return;

        delete[] m_Data;
        m_Data = nullptr;
        m_Length = 0;
    }

    void Utf16String::init(std::size_t length)
    {
        cleanup();
        m_Length = length;
        m_Data = new wchar_t[(m_Length + 1) * sizeof(wchar_t)];
        m_Data[m_Length] = '\0';
    }
}