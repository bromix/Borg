#include "Borg/BasicStringBuffer.h"
#include "Borg/Exception.h"

namespace Borg
{
    template <>
    int BasicStringBuffer<char>::CompareTo(const BasicStringBuffer<char> &rhs) const
    {
        return strcmp(m_Ptr, rhs.m_Ptr);
    }

    template<>
    BasicStringBuffer<char> BasicStringBuffer<char>::ToLower() const
    {
        BasicStringBuffer<char> copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::tolower(copy[i]);

        return copy;
    }

    template<>
    BasicStringBuffer<char> BasicStringBuffer<char>::ToUpper() const
    {
        BasicStringBuffer<char> copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::toupper(copy[i]);

        return copy;
    }

    template<>
    bool BasicStringBuffer<char>::StartsWith(const BasicStringBuffer<char> &input) const
    {
        if (input.Length() > Length())
            return false;
        auto result = strncmp(m_Ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    bool BasicStringBuffer<char>::EndsWith(const BasicStringBuffer<char> &input) const
    {
        if (input.Length() > Length())
            return false;

        // We must subtract the null-termination '\0'
        auto ptr = &m_Ptr[Length() - input.Length()];
        auto result = strncmp(ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    BasicStringBuffer<char> BasicStringBuffer<char>::CopyFrom(std::basic_string_view<char> input)
    {
        BasicStringBuffer<char> cb;
        cb.prepareStringBuffer(input, true);
        return cb;
    }

    template <>
    BasicStringBuffer<char> BasicStringBuffer<char>::ViewFrom(std::basic_string_view<char> input)
    {
        BasicStringBuffer<char> cb;
        cb.prepareStringBuffer(input, false);
        return cb;
    }

    BasicStringBuffer<char> BasicStringBuffer<char>::Insert(int startIndex, const BasicStringBuffer<char> &input) const
    {
        if (startIndex < 0 || startIndex > Length())
            throw ArgumentOutOfRangeException("startIndex");

        BasicStringBuffer<char> newString = BasicStringBuffer<char>(Length() + input.Length());

        char *targetData = newString.m_Ptr;
        char *sourceData = m_Ptr;

        if (startIndex > 0)
            std::strncpy(targetData, sourceData, startIndex);

        targetData += startIndex;
        std::strncpy(targetData, input.m_Ptr, input.Length());

        targetData += input.Length();
        sourceData += startIndex;
        std::strncpy(targetData, sourceData, Length() - startIndex);

        return newString;
    }
}