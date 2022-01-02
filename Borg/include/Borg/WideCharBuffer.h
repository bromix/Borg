#pragma once
#include "AbstractStringBuffer.h"

namespace Borg
{
    class WideCharBuffer final : public AbstractStringBuffer<wchar_t>
    {
    public:
        WideCharBuffer() : AbstractStringBuffer<wchar_t>() {}
        WideCharBuffer(const WideCharBuffer &input) : AbstractStringBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }
        WideCharBuffer(std::size_t length) : AbstractStringBuffer<wchar_t>(length)
        {
            m_Data = m_Ptr;
        }

        WideCharBuffer(const wchar_t *input) : WideCharBuffer(std::wstring_view(input)) {}
        WideCharBuffer(const std::wstring &input) : WideCharBuffer(std::wstring_view(input)) {}
        WideCharBuffer(std::wstring_view input) : AbstractStringBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }

        int CompareTo(const WideCharBuffer &rhs) const
        {
            return wcscmp(m_Ptr, rhs.m_Ptr);
        }

        WideCharBuffer ToLower() const
        {
            return L"";
        }

        WideCharBuffer ToUpper() const
        {
            return L"";
        }

        bool StartsWith(const WideCharBuffer &input) const
        {
            return false;
        }

        bool EndsWith(const WideCharBuffer &input) const
        {
            return false;
        }

        WideCharBuffer Insert(int startIndex, const WideCharBuffer& input) const
        {
            return L"";
        }
    private:
        wchar_t *m_Data;
    };
}