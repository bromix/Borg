#include <cwctype>
#include "Borg/BasicStringBuffer.h"
#include "Borg/Exception.h"

namespace Borg
{
    template<>
    int BasicStringBuffer<wchar_t>::CompareTo(const BasicStringBuffer<wchar_t> &rhs) const
    {
        return wcscmp(m_Ptr, rhs.m_Ptr);
    }

    template<>
    BasicStringBuffer<wchar_t> BasicStringBuffer<wchar_t>::ToLower() const
    {
        BasicStringBuffer<wchar_t> copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::towlower(copy[i]);

        return copy;
    }

    template<>
    BasicStringBuffer<wchar_t> BasicStringBuffer<wchar_t>::ToUpper() const
    {
        BasicStringBuffer<wchar_t> copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::towupper(copy[i]);

        return copy;
    }

    template<>
    bool BasicStringBuffer<wchar_t>::StartsWith(const BasicStringBuffer<wchar_t> &input) const
    {
        if (input.Length() > Length())
            return false;
        auto result = wcsncmp(m_Ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    bool BasicStringBuffer<wchar_t>::EndsWith(const BasicStringBuffer<wchar_t> &input) const
    {
        if (input.Length() > Length())
            return false;

        // We must subtract the null-termination '\0'
        auto ptr = &m_Ptr[Length() - input.Length()];
        auto result = wcsncmp(ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    BasicStringBuffer<wchar_t> BasicStringBuffer<wchar_t>::CopyFrom(std::basic_string_view<wchar_t> input)
    {
        BasicStringBuffer<wchar_t> wcb;
        wcb.prepareBuffer(input, true);
        return wcb;
    }

    template<>
    BasicStringBuffer<wchar_t> BasicStringBuffer<wchar_t>::ViewFrom(std::basic_string_view<wchar_t> input)
    {
        BasicStringBuffer<wchar_t> wcb;
        wcb.prepareBuffer(input, false);
        return wcb;
    }

    template<>
    BasicStringBuffer<wchar_t> BasicStringBuffer<wchar_t>::Insert(int startIndex, const BasicStringBuffer<wchar_t> &input) const
    {
        if (startIndex < 0 || startIndex > Length())
            throw ArgumentOutOfRangeException("startIndex");

        BasicStringBuffer<wchar_t> newString = BasicStringBuffer<wchar_t>(Length() + input.Length());

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