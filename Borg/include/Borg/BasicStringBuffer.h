#pragma once
#include "ArrayBuffer.h"
#include <string_view>

namespace Borg
{
    template <typename T>
    class BasicStringBuffer : protected ArrayBuffer<T>
    {
    public:
        BasicStringBuffer() : ArrayBuffer<T>() {}
        BasicStringBuffer(nullptr_t) : ArrayBuffer<T>() {}
        BasicStringBuffer(const BasicStringBuffer<T> &input) : ArrayBuffer<T>(input) {}
        BasicStringBuffer(BasicStringBuffer<T> &&input) : ArrayBuffer<T>(std::move(input)) {}

        /**
         * @brief Creates a StringBuffer with the given length of "characters".
         * @remark The length will be calculated into GetCapacity for the internal buffer.
         *
         * @param length
         */
        BasicStringBuffer(std::size_t length) : ArrayBuffer<T>((length + 1) * sizeof(T))
        {
            m_Ptr[length] = '\0';
        }

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

        std::size_t GetCapacity() const
        {
            return ArrayBuffer<T>::GetCapacity();
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
        BasicStringBuffer<T> &Detach()
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

        BasicStringBuffer<T> &operator=(const BasicStringBuffer<T> &input)
        {
            ArrayBuffer<T>::operator=(input);
            return *this;
        }

        BasicStringBuffer<T> &operator=(BasicStringBuffer<T> &&input)
        {
            ArrayBuffer<T>::operator=(std::move(input));
            return *this;
        }

        int CompareTo(const BasicStringBuffer<T> &rhs) const;
        BasicStringBuffer<T> ToLower() const;
        BasicStringBuffer<T> ToUpper() const;
        bool StartsWith(const BasicStringBuffer<T> &input) const;
        bool EndsWith(const BasicStringBuffer<T> &input) const;
        BasicStringBuffer<T> Insert(int startIndex, const BasicStringBuffer<T> &input) const;

        static BasicStringBuffer<T> CopyFrom(std::basic_string_view<T> input);
        static BasicStringBuffer<T> ViewFrom(std::basic_string_view<T> input);

    protected:
        void prepareBuffer(std::basic_string_view<T> input, bool createCopy = false)
        {
            // we add +1 because of the null-termination.
            m_Capacity = (input.length() + 1) * sizeof(T);

            if (createCopy)
            {
                m_IsDetached = false;
                m_Ptr = new T[m_Capacity];
                m_Ptr[input.length()] = '\0'; // we must add the null-termination while copying.
                memcpy_s(m_Ptr, m_Capacity, input.data(), input.length() * sizeof(T));
            }
            else
            {
                m_IsDetached = true;
                m_Ptr = const_cast<T *>(input.data());
            }
        }
    };

    using StringBuffer = BasicStringBuffer<char>;
    using WideStringBuffer = BasicStringBuffer<wchar_t>;
}