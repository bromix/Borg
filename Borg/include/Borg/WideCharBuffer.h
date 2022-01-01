#pragma once
#include "AbstractStringBuffer.h"

namespace Borg
{
    class WideCharBuffer : public AbstractStringBuffer<wchar_t>
    {
    public:
        WideCharBuffer(std::size_t length) : AbstractStringBuffer<wchar_t>(length)
        {
            m_Data = m_Ptr;
        }

        WideCharBuffer(std::wstring_view input) : AbstractStringBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }

    private:
        wchar_t *m_Data;
    };
}