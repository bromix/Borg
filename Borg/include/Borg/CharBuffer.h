#pragma once
#include "EncodingBuffer.h"
#include <cctype>

namespace Borg
{
    class CharBuffer : public EncodingBuffer<char>
    {
    public:
        using CharType = char;

        CharBuffer() : EncodingBuffer<char>() {}
        CharBuffer(nullptr_t) : EncodingBuffer<char>() {}
        CharBuffer(const CharBuffer &input) : EncodingBuffer<char>(input) {}

        CharBuffer(CharBuffer &&input) : EncodingBuffer<char>(std::move(input)) {}

        CharBuffer(std::size_t length) : EncodingBuffer<char>(length) {}

        CharBuffer &operator=(const CharBuffer &input)
        {
            EncodingBuffer<char>::operator=(input);
            return *this;
        }

        CharBuffer &operator=(CharBuffer &&input)
        {
            EncodingBuffer<char>::operator=(std::move(input));
            return *this;
        }

        int CompareTo(const CharBuffer &rhs) const
        {
            return strcmp(m_Ptr, rhs.m_Ptr);
        }

        CharBuffer ToLower() const
        {
            CharBuffer copy(*this);
            for (std::size_t i = 0; i < copy.Length(); i++)
                copy[i] = std::tolower(copy[i]);

            return copy;
        }

        CharBuffer ToUpper() const
        {
            CharBuffer copy(*this);
            for (std::size_t i = 0; i < copy.Length(); i++)
                copy[i] = std::toupper(copy[i]);

            return copy;
        }

        bool StartsWith(const CharBuffer &input) const
        {
            if (input.Length() > Length())
                return false;
            auto result = strncmp(m_Ptr, input.m_Ptr, input.Length());
            return result == 0;
        }

        bool EndsWith(const CharBuffer &input) const
        {
            if (input.Length() > Length())
                return false;

            // We must subtract the null-termination '\0'
            auto ptr = &m_Ptr[Length() - input.Length()];
            auto result = strncmp(ptr, input.m_Ptr, input.Length());
            return result == 0;
        }

        static CharBuffer CopyFrom(std::string_view input)
        {
            CharBuffer cb;
            cb.prepareBuffer(input, true);
            return cb;
        }

        static CharBuffer ViewFrom(std::string_view input)
        {
            CharBuffer cb;
            cb.prepareBuffer(input, false);
            return cb;
        }

        CharBuffer Insert(int startIndex, const CharBuffer &input) const;
    };
}