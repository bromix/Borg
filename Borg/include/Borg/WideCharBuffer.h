#pragma once
#include "EncodingBuffer.h"
#include <cwctype>

namespace Borg
{
    class WideCharBuffer final : public EncodingBuffer<wchar_t>
    {
    public:
        WideCharBuffer() : EncodingBuffer<wchar_t>() {}
        WideCharBuffer(const WideCharBuffer &input) : EncodingBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
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
            return false;
        }

        bool EndsWith(const WideCharBuffer &input) const
        {
            return false;
        }

        WideCharBuffer Insert(int startIndex, const WideCharBuffer &input) const
        {
            return L"";
        }

    private:
        wchar_t *m_Data;
    };
}