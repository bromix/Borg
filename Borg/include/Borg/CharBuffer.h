#pragma once
#include "EncodingBuffer.h"

namespace Borg
{
    class CharBuffer : public EncodingBuffer<char>
    {
    public:
        CharBuffer(const CharBuffer &input) : EncodingBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }
        CharBuffer(std::size_t length) : EncodingBuffer<char>(length)
        {
            m_Data = m_Ptr;
        }
        CharBuffer(const char *input) : CharBuffer(std::string_view(input)) {}
        CharBuffer(const std::string& input) : CharBuffer(std::string_view(input)){}
        CharBuffer(std::string_view input) : EncodingBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }
    private:
        char *m_Data;
    };
}