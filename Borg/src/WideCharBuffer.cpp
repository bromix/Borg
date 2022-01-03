#include "Borg/WideCharBuffer.h"
#include "Borg/Exception.h"

namespace Borg
{
    WideCharBuffer WideCharBuffer::Insert(int startIndex, const WideCharBuffer &input) const
    {
        if (startIndex < 0 || startIndex > Length())
            throw ArgumentOutOfRangeException("startIndex");

        WideCharBuffer newString = WideCharBuffer(Length() + input.Length());

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