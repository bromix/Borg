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

        CharBuffer(CharBuffer &&input) : EncodingBuffer<char>(std::move(input))
        {
            m_Data = m_Ptr;
        }

        CharBuffer(std::size_t length) : EncodingBuffer<char>(length)
        {
            m_Data = m_Ptr;
        }
        CharBuffer(const char *input) : EncodingBuffer<char>(input) {}
        CharBuffer(const std::string &input) : CharBuffer(std::string_view(input)) {}
        CharBuffer(std::string_view input) : EncodingBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }

        CharBuffer &operator=(const CharBuffer &input)
        {
            EncodingBuffer<char>::operator=(input);
            m_Data = m_Ptr;
            return *this;
        }

        CharBuffer &operator=(CharBuffer &&input)
        {
            EncodingBuffer<char>::operator=(std::move(input));
            m_Data = m_Ptr;
            return *this;
        }

    private:
        char *m_Data;
    };
}