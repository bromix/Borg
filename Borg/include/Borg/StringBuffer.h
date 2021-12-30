#pragma once
#include "Buffer.h"
#include "IStringBuffer.h"
#include <string_view>

namespace Borg
{
    template <typename T, StringEncoding TEncoding>
    class StringBuffer : public Buffer<T>, public IStringBuffer
    {
    public:
        StringBuffer(nullptr_t) : Buffer<T>(nullptr){};

        StringBuffer(const StringBuffer<T, TEncoding> &input) : Buffer<T>(input)
        {
        }

        StringBuffer<T, TEncoding>& operator=(const StringBuffer<T, TEncoding>& input)
        {
            Buffer<T>::operator=(input);
            return *this;
        }

        StringBuffer(StringBuffer<T, TEncoding> &&input): Buffer<T>(std::move(input))
        {
        }

        StringBuffer<T, TEncoding>& operator=(StringBuffer<T, TEncoding>&& input)
        {
            Buffer<T>::operator=(std::move(input));
            return *this;
        }

        StringBuffer(std::basic_string_view<T> input) : StringBuffer(input.length())
        {
            CopyFrom(input);
        }

        /**
         * @brief Creates a new StringBuffer with null-termination.
         *
         * @param count
         */
        StringBuffer(std::size_t count) : Buffer<T>(count + 1)
        {
            m_Data[count] = '\0';
        }

        /**
         * @brief Returns the count without the null-termination.
         *
         * @return std::size_t
         */
        std::size_t Count() const override
        {
            return m_Count > 0 ? m_Count - 1 : 0;
        }

        StringEncoding Encoding() const override
        {
            return TEncoding;
        }

        /**
         * @brief Cast operator to std::basic_string_view<T>.
         *
         * @return std::basic_string_view<T>
         */
        operator std::basic_string_view<T>() const
        {
            return m_Data;
        }

        operator std::basic_string<T>() const
        {
            return std::basic_string<T>(m_Data);
        }

        StringBuffer<T, TEncoding> &Detach() override
        {
            Buffer<T>::Detach();
            return *this;
        }
    };

    using CharBuffer = StringBuffer<char, StringEncoding::Utf8>;
    using WideCharBuffer = StringBuffer<wchar_t, StringEncoding::Utf16>;
#ifdef __cpp_lib_char8_t
    using Char8Buffer = StringBuffer<char8_t, StringEncoding::Utf8>;
#else
    using Char8Buffer = StringBuffer<char, StringEncoding::Utf8>;
#endif // __cpp_lib_char8_t
    using Char16Buffer = StringBuffer<char16_t, StringEncoding::Utf16>;
    using Char32Buffer = StringBuffer<char32_t, StringEncoding::Utf32>;
}