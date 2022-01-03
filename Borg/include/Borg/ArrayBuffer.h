#pragma once

namespace Borg
{
    template <typename T>
    class ArrayBuffer
    {
    public:
        /**
         * @brief Empty default constructor.
         */
        ArrayBuffer() = default;

        /**
         * @brief Creates an ArrayBuffer with the given size in bytes.
         *
         * @param byteLength
         */
        ArrayBuffer(std::size_t byteLength)
        {
            m_ByteLength = byteLength;
            m_Ptr = new T[m_ByteLength];
        }

        ArrayBuffer(const ArrayBuffer<T> &input)
        {
            m_ByteLength = input.m_ByteLength;
            m_IsDetached = input.m_IsDetached;

            /*
            If the input is detached, we must also be detached and therefore
            will only point to the same address.
            The given input won't delete the internal buffer either.
            */
            if (input.m_IsDetached)
                m_Ptr = input.m_Ptr;
            else if(input.m_ByteLength > 0 && input.m_Ptr != nullptr)
            {
                m_Ptr = new T[m_ByteLength];
                copy(input);
            }
        }

        ArrayBuffer(ArrayBuffer<T> &&input)
        {
            swap(std::move(input));
        }

        ~ArrayBuffer()
        {
            clear();
        }

        /**
         * @brief Returns the size in bytes of the ArrayBuffer
         *
         * @return std::size_t size in bytes.
         */
        std::size_t ByteLength() const
        {
            return m_ByteLength;
        }

        /**
         * @brief Returns the length of in form of entries and not the length in bytes.
         *
         * @return std::size_t
         */
        std::size_t Length() const
        {
            return m_ByteLength / sizeof(T);
        }

        /**
         * @brief Determines whether the ArrayBuffer is empty or not.
         *
         * @return true if the ArrayBuffer is empty.
         * @return false if the ArrayBuffer is not emptry.
         */
        bool IsEmpty() const
        {
            return m_ByteLength == 0;
        }

        bool IsNull() const
        {
            return m_Ptr == nullptr;
        }

        /**
         * @brief Detaches the ArrayBuffer from the underlying Buffer.
         * @remark This will not free resources after the ArrayBuffer is out of scope or deleted.
         * @remark The caller must free the resource.
         *
         * @return Buffer<T>&
         */
        ArrayBuffer<T> &Detach()
        {
            m_IsDetached = true;
            return *this;
        }

        /**
         * @brief Determines whether the ArrayBuffer is detached or not.
         *
         * @return true
         * @return false
         */
        bool IsDetached() const
        {
            return m_IsDetached;
        }

        /**
         * @brief Cast operator.
         *
         * @return T *
         */
        operator T *() const
        {
            return m_Ptr;
        }

        /**
         * @brief Returns the pointer the internal buffer.
         *
         * @return T*
         */
        T *Data() const
        {
            return m_Ptr;
        }

        ArrayBuffer<T> &operator=(const ArrayBuffer<T> &input)
        {
            clear();
            copy(input);

            return *this;
        }

        ArrayBuffer<T> &operator=(ArrayBuffer<T> &&input)
        {
            clear();
            swap(std::move(input));

            return *this;
        }

    protected:
        void copy(const ArrayBuffer<T> &input)
        {
            memcpy_s(m_Ptr, m_ByteLength, input.m_Ptr, input.m_ByteLength);
        }

        void swap(ArrayBuffer<T> &&input)
        {
            std::swap(m_IsDetached, input.m_IsDetached);
            std::swap(m_ByteLength, input.m_ByteLength);
            std::swap(m_Ptr, input.m_Ptr);
        }

        void clear()
        {
            if (m_IsDetached || m_Ptr == nullptr)
                return;
            delete[] m_Ptr;
            m_Ptr = nullptr;
            m_ByteLength = 0;
            m_IsDetached = false;
        }

        bool m_IsDetached = false;
        std::size_t m_ByteLength = 0;
        T *m_Ptr = nullptr;
    };
} // namespace Borg
