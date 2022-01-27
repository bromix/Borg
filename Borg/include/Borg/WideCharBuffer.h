#pragma once
#include "BasicStringBuffer.h"
#include <cwctype>

namespace Borg
{
    class WideCharBuffer final : public BasicStringBuffer<wchar_t>
    {
    public:
        using CharType = wchar_t;

        WideCharBuffer() : BasicStringBuffer<wchar_t>() {}
        WideCharBuffer(nullptr_t) : BasicStringBuffer<wchar_t>() {}
        WideCharBuffer(WideCharBuffer &&input) : BasicStringBuffer<wchar_t>(std::move(input)) {}

        WideCharBuffer &operator=(WideCharBuffer &&input)
        {
            BasicStringBuffer<wchar_t>::operator=(std::move(input));
            return *this;
        }

        WideCharBuffer(const WideCharBuffer &input) : BasicStringBuffer<wchar_t>(input) {}

        WideCharBuffer &operator=(const WideCharBuffer &input)
        {
            BasicStringBuffer<wchar_t>::operator=(input);
            return *this;
        }

        WideCharBuffer(std::size_t length) : BasicStringBuffer<wchar_t>(length) {}

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

        static WideCharBuffer CopyFrom(std::wstring_view input)
        {
            WideCharBuffer wcb;
            wcb.prepareBuffer(input, true);
            return wcb;
        }

        static WideCharBuffer ViewFrom(std::wstring_view input)
        {
            WideCharBuffer wcb;
            wcb.prepareBuffer(input, false);
            return wcb;
        }

        WideCharBuffer Insert(int startIndex, const WideCharBuffer &input) const;
    };
}