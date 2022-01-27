#include <cwctype>
#include "Borg/BasicStringBuffer.h"
#include "Borg/Exception.h"

namespace Borg
{
    template<>
    int WideStringBuffer::CompareTo(const WideStringBuffer &rhs) const
    {
        return wcscmp(m_Ptr, rhs.m_Ptr);
    }

    template<>
    WideStringBuffer WideStringBuffer::ToLower() const
    {
        WideStringBuffer copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::towlower(copy[i]);

        return copy;
    }

    template<>
    WideStringBuffer WideStringBuffer::ToUpper() const
    {
        WideStringBuffer copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::towupper(copy[i]);

        return copy;
    }

    template<>
    bool WideStringBuffer::StartsWith(const WideStringBuffer &input) const
    {
        if (input.Length() > Length())
            return false;
        auto result = wcsncmp(m_Ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    bool WideStringBuffer::EndsWith(const WideStringBuffer &input) const
    {
        if (input.Length() > Length())
            return false;

        // We must subtract the null-termination '\0'
        auto ptr = &m_Ptr[Length() - input.Length()];
        auto result = wcsncmp(ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    WideStringBuffer WideStringBuffer::CopyFrom(std::basic_string_view<wchar_t> input)
    {
        WideStringBuffer wcb;
        wcb.prepareStringBuffer(input, true);
        return wcb;
    }

    template<>
    WideStringBuffer WideStringBuffer::ViewFrom(std::basic_string_view<wchar_t> input)
    {
        WideStringBuffer wcb;
        wcb.prepareStringBuffer(input, false);
        return wcb;
    }

    template<>
    WideStringBuffer WideStringBuffer::Insert(int startIndex, const WideStringBuffer &input) const
    {
        if (startIndex < 0 || startIndex > Length())
            throw ArgumentOutOfRangeException("startIndex");

        WideStringBuffer newString = WideStringBuffer(Length() + input.Length());

        wchar_t *targetData = newString.m_Ptr;
        wchar_t *sourceData = m_Ptr;

        if (startIndex > 0)
            std::wmemcpy(targetData, sourceData, startIndex);

        targetData += startIndex;
        std::wmemcpy(targetData, input.m_Ptr, input.Length());

        targetData += input.Length();
        sourceData += startIndex;
        std::wmemcpy(targetData, sourceData, Length() - startIndex);

        return newString;
    }
}