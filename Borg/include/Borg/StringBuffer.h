#pragma once
#include "ArrayBuffer.h"
#include "IStringBuffer.h"
#include <string_view>

namespace Borg
{
    template <typename T>
    class StringBuffer : public ArrayBuffer<T>, public IStringBuffer
    {
    public:
        /**
         * @brief Empty default constructor.
         */
        StringBuffer() : ArrayBuffer<T>() {}

        StringBuffer(const StringBuffer<T> &input) : ArrayBuffer<T>(input) {}

        StringBuffer(StringBuffer<T> &&input) : ArrayBuffer<T>(std::move(input)) {}

        /**
         * @brief Creates a StringBuffer with the given length of "characters".
         * @remark The length will be calculated into ByteLength for the internal buffer.
         *
         * @param length
         */
        StringBuffer(std::size_t length) : ArrayBuffer<T>((length + 1) * sizeof(T))
        {
            m_Ptr[length] = '\0';
        }

        StringBuffer(std::basic_string_view<T> input, bool createCopy = false)
            : ArrayBuffer<T>()
        {
            // we add +1 because of the null-termination.
            m_ByteLength = (input.length() + 1) * sizeof(T);

            if (createCopy)
            {
                m_IsDetached = false;
                m_Ptr = new T[m_ByteLength];
                m_Ptr[input.length()] = '\0'; // we must add the null-termination while copying.
                memcpy_s(m_Ptr, m_ByteLength, input.data(), input.length() * sizeof(T));
            }
            else
            {
                m_IsDetached = true;
                m_Ptr = const_cast<T *>(input.data());
            }
        }

        /**
         * @brief Returns the length of the StringBuffer without the null-termination.
         *
         * @return std::size_t
         */
        std::size_t Length() const
        {
            auto length = ArrayBuffer<T>::Length();
            return length > 0 ? length - 1 : 0;
        }

        /**
         * @brief Cast operator to std::basic_string_view<T>.
         *
         * @return std::basic_string_view<T>
         */
        operator std::basic_string_view<T>() const
        {
            return m_Ptr;
        }

        operator std::basic_string<T>() const
        {
            return std::basic_string<T>(m_Ptr);
        }

        /**
         * @brief Detaches the StringBuffer from the underlying Buffer.
         * @remark This will not free resources after the ArrayBuffer is out of scope or deleted.
         * @remark The caller must free the resource.
         *
         * @return StringBuffer<T>&
         */
        StringBuffer<T> &Detach()
        {
            ArrayBuffer<T>::Detach();
            return *this;
        }

        StringBuffer<T> &operator=(const StringBuffer<T> &input)
        {
            ArrayBuffer<T>::operator=(input);
            return *this;
        }

        StringBuffer<T> &operator=(StringBuffer<T> &&input)
        {
            ArrayBuffer<T>::operator=(std::move(input));
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