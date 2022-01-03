#pragma once
#include "EncodingBuffer.h"
#include <cwctype>

namespace Borg
{
    class WideCharBuffer final : public EncodingBuffer<wchar_t>
    {
    public:
        WideCharBuffer() : EncodingBuffer<wchar_t>() {}

        WideCharBuffer(WideCharBuffer &&input) : EncodingBuffer<wchar_t>(std::move(input))
        {
            m_Data = m_Ptr;
        }

        WideCharBuffer &operator=(WideCharBuffer &&input)
        {
            EncodingBuffer<wchar_t>::operator=(std::move(input));
            return *this;
        }

        WideCharBuffer(const WideCharBuffer &input) : EncodingBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }

        WideCharBuffer &operator=(const WideCharBuffer &input)
        {
            EncodingBuffer<wchar_t>::operator=(input);
            return *this;
        }

        WideCharBuffer(std::size_t length) : EncodingBuffer<wchar_t>(length)
        {
            m_Data = m_Ptr;
        }

        WideCharBuffer(const wchar_t *input) : WideCharBuffer(std::wstring_view(input)) {}
        WideCharBuffer(const std::wstring &input) : WideCharBuffer(std::wstring_view(input)) {}
        WideCharBuffer(std::wstring_view input) : EncodingBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }

        int CompareTo(const WideCharBuffer &rhs) const
        {
            return wcscmp(m_Ptr, rhs.m_Ptr);
        }

        WideCharBuffer ToLower() const
        {
            WideCharBuffer copy(*this);
            for (std::size_t i = 0; i < copy.Length(); i++)
                copy[i] = std::towlower(copy[i]);

            return copy;
        }

        WideCharBuffer ToUpper() const
        {
            WideCharBuffer copy(*this);
            for (std::size_t i = 0; i < copy.Length(); i++)
                copy[i] = std::towupper(copy[i]);

            return copy;
        }

        bool StartsWith(const WideCharBuffer &input) const
        {
            if (input.Length() > Length())
                return false;
            auto result = wcsncmp(m_Ptr, input.m_Ptr, input.Length());
            return result == 0;
        }

        bool EndsWith(const WideCharBuffer &input) const
        {
            if (input.Length() > Length())
                return false;

            // We must subtract the null-termination '\0'
            auto ptr = &m_Ptr[Length() - input.Length()];
            auto result = wcsncmp(ptr, input.m_Ptr, input.Length());
            return result == 0;
        }

        WideCharBuffer Insert(int startIndex, const WideCharBuffer &input) const;

    private:
        wchar_t *m_Data;
    };
}