#pragma once
#include "ArrayBuffer.h"
#include <string_view>

namespace Borg
{
    template <typename T>
    class EncodingBuffer : protected ArrayBuffer<T>
    {
    public:
        EncodingBuffer() : ArrayBuffer<T>() {}

        EncodingBuffer(const EncodingBuffer<T> &input) : ArrayBuffer<T>(input) {}

        EncodingBuffer(EncodingBuffer<T> &&input) : ArrayBuffer<T>(std::move(input)) {}

        /**
         * @brief Creates a StringBuffer with the given length of "characters".
         * @remark The length will be calculated into ByteLength for the internal buffer.
         *
         * @param length
         */
        EncodingBuffer(std::size_t length) : ArrayBuffer<T>((length + 1) * sizeof(T))
        {
            m_Ptr[length] = '\0';
        }

        // EncodingBuffer(const T *input, bool createCopy = false) : ArrayBuffer<T>()
        // {
        //     if(input != nullptr)
        //         prepareBuffer(input, createCopy);
        // }

        // EncodingBuffer(std::basic_string_view<T> input, bool createCopy = false)
        //     : ArrayBuffer<T>()
        // {
        //     prepareBuffer(input, createCopy);
        // }

        bool IsEmpty() const
        {
            return Length() == 0;
        }

        bool IsNull() const
        {
            return ArrayBuffer<T>::IsNull();
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

        std::size_t ByteLength() const
        {
            return ArrayBuffer<T>::ByteLength();
        }

        operator T *() const
        {
            return m_Ptr;
        }

        T *Data() const
        {
            return m_Ptr;
        }

        /**
         * @brief Detaches the StringBuffer from the underlying Buffer.
         * @remark This will not free resources after the ArrayBuffer is out of scope or deleted.
         * @remark The caller must free the resource.
         *
         * @return StringBuffer<T>&
         */
        EncodingBuffer<T> &Detach()
        {
            ArrayBuffer<T>::Detach();
            return *this;
        }

        T &operator[](std::size_t index)
        {
            // TODO: check index
            return m_Ptr[index];
        }

        const T &operator[](std::size_t index) const
        {
            // TODO: check index
            return m_Ptr[index];
        }

        EncodingBuffer<T> &operator=(const EncodingBuffer<T> &input)
        {
            ArrayBuffer<T>::operator=(input);
            return *this;
        }

        EncodingBuffer<T> &operator=(EncodingBuffer<T> &&input)
        {
            ArrayBuffer<T>::operator=(std::move(input));
            return *this;
        }

    protected:
        void prepareBuffer(std::basic_string_view<T> input, bool createCopy = false)
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
    };
}