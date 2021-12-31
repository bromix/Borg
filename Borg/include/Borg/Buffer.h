#pragma once
#include <string_view>
#include "Borg/Exception.h"

namespace Borg
{
    template <typename T>
    class Buffer
    {
    public:
        /**
         * @brief Constructor for assigning nullptr.
         */
        Buffer(nullptr_t);

        /**
         * @brief Copy constructor for another Buffer<T>.
         *
         * @param input
         */
        Buffer(const Buffer<T> &input);

        /**
         * @brief Move constructor for another Buffer<T>.
         *
         * @param input
         */
        Buffer(Buffer<T> &&input);

        /**
         * @brief Constructor for reserving the internal buffer with given amount of data (not bytes!).
         *
         * @param count
         */
        Buffer(std::size_t count);
        ~Buffer();

        /**
         * @brief The size in bytes.
         *
         * @return std::size_t
         */
        std::size_t Size() const;

        /**
         * @brief The count of data
         *
         * @return std::size_t
         */
        virtual std::size_t Count() const;

        /**
         * @brief Indicates if the Buffer is null.
         *
         * @return true is null, false otherwise.
         */
        bool IsNull() const;

        /**
         * @brief Indicates if the Buffer is empty (Count = 0, Size = 0, ...).
         *
         * @return true if empty, false otherwise.
         */
        bool IsEmpty() const;

        /**
         * @brief Indicates wether the Buffer is null or empty.
         *
         * @return true
         * @return false
         */
        bool IsNullOrEmpty() const;

        /**
         * @brief Pointer to the beginning of the data.
         *
         * @return T*
         */
        T *Data() const;

        /**
         * @brief Pointer to the beginning of the data.
         *
         * @return const T*
         */
        const T *Data();

        /**
         * @brief Pointer to the beginning of the data.
         *
         * @return T*
         */
        operator T *() const;

        /**
         * @brief Pointer to the beginning of the data.
         *
         * @return const T*
         */
        operator const T *();

        T &operator[](std::size_t index) const;
        const T &operator[](std::size_t index);

        Buffer<T> &operator=(const Buffer<T> &input);
        Buffer<T> &operator=(Buffer<T> &&input);

        void CopyFrom(const Buffer<T> &input);
        void CopyFrom(const T *input, std::size_t size);

        virtual Buffer<T> &Detach();

    protected:
        /**
         * @brief Deletes the internal data pointer.
         */
        void reset();

        std::size_t m_Size = 0;
        std::size_t m_Count = 0;
        bool m_Detached = false;

        T *m_Data = nullptr;
    };

    template <typename T>
    Buffer<T>::Buffer(nullptr_t)
        : m_Data(nullptr), m_Size(0), m_Count(0)
    {
    }

    template <typename T>
    Buffer<T>::Buffer(const Buffer<T> &input)
    {
        *this = input;
    }

    template <typename T>
    Buffer<T>::Buffer(Buffer<T> &&input)
        : m_Data(nullptr), m_Size(0), m_Count(0)
    {
        *this = std::move(input);
    }

    template <typename T>
    Buffer<T>::Buffer(std::size_t count)
        : m_Count(count), m_Size(count * sizeof(T))
    {
        m_Data = new T[m_Size];
    }

    template <typename T>
    Buffer<T>::~Buffer()
    {
        if (!m_Detached)
            reset();
    }

    template <typename T>
    bool Buffer<T>::IsNull() const
    {
        return m_Data == nullptr;
    }

    template <typename T>
    bool Buffer<T>::IsEmpty() const
    {
        return m_Count == 0;
    }

    template <typename T>
    bool Buffer<T>::IsNullOrEmpty() const
    {
        return IsNull() || IsEmpty();
    }

    template <typename T>
    T *Buffer<T>::Data() const
    {
        return m_Data;
    }

    template <typename T>
    const T *Buffer<T>::Data()
    {
        return m_Data;
    }

    template <typename T>
    Buffer<T>::operator T *() const
    {
        return m_Data;
    }

    template <typename T>
    Buffer<T>::operator const T *()
    {
        return m_Data;
    }

    template <typename T>
    T &Buffer<T>::operator[](std::size_t index) const
    {
        if (index >= m_Count)
            throw ArgumentOutOfRangeException("index");
        return m_Data[index];
    }

    template <typename T>
    const T &Buffer<T>::operator[](std::size_t index)
    {
        if (index >= m_Count)
            throw ArgumentOutOfRangeException("index");
        return m_Data[index];
    }

    template <typename T>
    std::size_t Buffer<T>::Size() const
    {
        return m_Size;
    }

    template <typename T>
    std::size_t Buffer<T>::Count() const
    {
        return m_Count;
    }

    template <typename T>
    void Buffer<T>::CopyFrom(const Buffer<T> &input)
    {
        if (input.Count() > m_Count)
            throw ArgumentOutOfRangeException("input.Count()");

        std::memcpy(m_Data, input.Data(), input.Size());
    }

    template<typename T>
    void Buffer<T>::CopyFrom(const T *input, std::size_t size)
    {
        if (size > m_Size)
            throw ArgumentOutOfRangeException("input.Count()");

        std::memcpy(m_Data, input, size);
    }

    template <typename T>
    Buffer<T> &Buffer<T>::operator=(const Buffer<T> &input)
    {
        reset();

        m_Size = input.m_Size;
        m_Data = new T[m_Size];
        m_Count = input.m_Count;
        m_Detached = input.m_Detached;
        CopyFrom(input);
        return *this;
    }

    template <typename T>
    Buffer<T> &Buffer<T>::operator=(Buffer<T> &&input)
    {
        reset();

        std::swap(m_Data, input.m_Data);
        std::swap(m_Count, input.m_Count);
        std::swap(m_Size, input.m_Size);
        std::swap(m_Detached, input.m_Detached);

        return *this;
    }

    template <typename T>
    void Buffer<T>::reset()
    {
        if (m_Data == nullptr)
            return;

        delete[] m_Data;
        m_Data = nullptr;
        m_Detached = false;
        m_Count = 0;
        m_Size = 0;
    }

    template <typename T>
    Buffer<T> &Buffer<T>::Detach()
    {
        m_Detached = true;
        return *this;
    }

    using ByteBuffer = Buffer<std::byte>;
} // namespace Borg
