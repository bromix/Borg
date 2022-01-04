#include "Borg/CharBuffer.h"
#include "Borg/Exception.h"

namespace Borg
{
    CharBuffer CharBuffer::Insert(int startIndex, const CharBuffer &input) const
    {
        if (startIndex < 0 || startIndex > Length())
            throw ArgumentOutOfRangeException("startIndex");

        CharBuffer newString = CharBuffer(Length() + input.Length());

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