#include "Borg/BasicStringBuffer.h"
#include "Borg/Exception.h"

namespace Borg
{
    template <>
    int StringBuffer::CompareTo(const StringBuffer &rhs) const
    {
        return strcmp(m_Ptr, rhs.m_Ptr);
    }

    template<>
    StringBuffer StringBuffer::ToLower() const
    {
        StringBuffer copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::tolower(copy[i]);

        return copy;
    }

    template<>
    StringBuffer StringBuffer::ToUpper() const
    {
        StringBuffer copy(*this);
        for (std::size_t i = 0; i < copy.Length(); i++)
            copy[i] = std::toupper(copy[i]);

        return copy;
    }

    template<>
    bool StringBuffer::StartsWith(const StringBuffer &input) const
    {
        if (input.Length() > Length())
            return false;
        auto result = strncmp(m_Ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    bool StringBuffer::EndsWith(const StringBuffer &input) const
    {
        if (input.Length() > Length())
            return false;

        // We must subtract the null-termination '\0'
        auto ptr = &m_Ptr[Length() - input.Length()];
        auto result = strncmp(ptr, input.m_Ptr, input.Length());
        return result == 0;
    }

    template<>
    StringBuffer StringBuffer::CopyFrom(std::basic_string_view<char> input)
    {
        StringBuffer cb;
        cb.prepareStringBuffer(input, true);
        return cb;
    }

    template <>
    StringBuffer StringBuffer::ViewFrom(std::basic_string_view<char> input)
    {
        StringBuffer cb;
        cb.prepareStringBuffer(input, false);
        return cb;
    }

    StringBuffer StringBuffer::Insert(int startIndex, const StringBuffer &input) const
    {
        if (startIndex < 0 || startIndex > Length())
            throw ArgumentOutOfRangeException("startIndex");

        StringBuffer newString = StringBuffer(Length() + input.Length());

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