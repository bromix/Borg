#pragma once
#include "Buffer.h"
#include "IStringBuffer.h"
#include <string_view>

namespace Borg
{
    template <typename T>
    class StringBuffer : public Buffer<T>, public IStringBuffer
    {
    public:
        /**
         * @brief Construct for a nullptr.
         */
        StringBuffer(nullptr_t) : Buffer<T>(nullptr){};

        /**
         * @brief Copy constructor.
         *
         * @param input
         */
        StringBuffer(const StringBuffer<T> &input) : Buffer<T>(input) {}

        /**
         * @brief Copy assignment operator.
         *
         * @param input
         * @return StringBuffer<T>&
         */
        StringBuffer<T> &operator=(const StringBuffer<T> &input)
        {
            Buffer<T>::operator=(input);
            return *this;
        }

        /**
         * @brief Move constructor.
         *
         * @param input
         */
        StringBuffer(StringBuffer<T> &&input) : Buffer<T>(std::move(input)) {}

        StringBuffer<T> &operator=(StringBuffer<T> &&input)
        {
            Buffer<T>::operator=(std::move(input));
            return *this;
        }

        /**
         * @brief Move assignment operator.
         *
         * @param input
         */
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

        void CopyFrom(std::basic_string_view<T> input)
        {
            Buffer<T>::CopyFrom(input.data(), input.length() * sizeof(T));
        }

        /**
         * @brief Detach the buffer from the internal buffer.
         *
         * @remark The caller has to release the buffer.
         *
         * @return StringBuffer<T>&
         */
        StringBuffer<T> &Detach() override
        {
            Buffer<T>::Detach();
            return *this;
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