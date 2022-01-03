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

        CharBuffer(const char *input, bool createCopy = true) : EncodingBuffer<char>(input, createCopy)
        {
            m_Data = m_Ptr;
        }

        CharBuffer(const std::string &input, bool createCopy = true) : CharBuffer(std::string_view(input), createCopy) {}

        CharBuffer(std::string_view input, bool createCopy = true) : EncodingBuffer<char>(input, createCopy)
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