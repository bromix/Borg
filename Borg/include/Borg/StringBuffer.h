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
        StringBuffer() : Buffer<T>(){};

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

        void CopyFrom(const T* input, std::size_t size)
        {
            Buffer<T>::CopyFrom(input, size);
        }

        static StringBuffer<T> ViewFrom(std::basic_string_view<T> input)
        {
            StringBuffer<T> buffer;
            buffer.initViaCount(input.length() + 1, true);
            buffer.m_Data = const_cast<T *>(input.data());
            return buffer;
        }

        static StringBuffer<T> CopyFrom(std::basic_string_view<T> input)
        {
            StringBuffer<T> buffer = FromLength(input.length());
            buffer.CopyFrom(input.data(), buffer.Count() * sizeof(T));
            return buffer;
        }

        static StringBuffer<T> FromLength(std::size_t length)
        {
            return FromCount(length);
        }

        static StringBuffer<T> FromCount(std::size_t count)
        {
            StringBuffer<T> buffer;
            buffer.initViaCount(count + 1);
            buffer.m_Data[count] = '\0';
            return buffer;
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