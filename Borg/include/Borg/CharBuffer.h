#pragma once
#include "AbstractStringBuffer.h"

namespace Borg
{
    class CharBuffer : public AbstractStringBuffer<char>
    {
    public:
        CharBuffer(const CharBuffer &input) : AbstractStringBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }
        CharBuffer(std::size_t length) : AbstractStringBuffer<char>(length)
        {
            m_Data = m_Ptr;
        }
        CharBuffer(const char *input) : CharBuffer(std::string_view(input)) {}
        CharBuffer(const std::string& input) : CharBuffer(std::string_view(input)){}
        CharBuffer(std::string_view input) : AbstractStringBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }
    private:
        char *m_Data;
    };
}