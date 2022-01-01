#pragma once
#include "AbstractStringBuffer.h"

namespace Borg
{
    class CharBuffer : public AbstractStringBuffer<char>
    {
    public:
        CharBuffer(std::size_t length) : AbstractStringBuffer<char>(length) {}
        CharBuffer(std::string_view input) : AbstractStringBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }
    private:
        char *m_Data;
    };
}