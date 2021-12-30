#pragma once
#include "Borg/Buffer.h"
#include <string_view>

namespace Borg
{
    template <typename T>
    class StringBuffer : public Buffer<T>
    {
    public:
        StringBuffer(nullptr_t) : Buffer<T>(nullptr) {}

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
    };

    using CharBuffer = StringBuffer<char>;
    using WideCharBuffer = StringBuffer<wchar_t>;
#ifdef __cpp_lib_char8_t
    using Char8Buffer = StringBuffer<char8_t>;
#endif // __cpp_lib_char8_t
    using Char16Buffer = StringBuffer<char16_t>;
    using Char32Buffer = StringBuffer<char32_t>;
}