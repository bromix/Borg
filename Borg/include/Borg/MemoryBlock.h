#pragma once
#include <string_view>
#include "Borg/Exception.h"

namespace Borg
{
    template <typename T>
    class MemoryBlock
    {
    public:
        /**
         * @brief Constructor for assigning nullptr.
         */
        MemoryBlock(nullptr_t);

        /**
         * @brief Copy constructor for another MemoryBlock<T>.
         *
         * @param input
         */
        MemoryBlock(const MemoryBlock<T> &input);

        /**
         * @brief Move constructor for another MemoryBlock<T>.
         *
         * @param input
         */
        MemoryBlock(MemoryBlock<T> &&input);

        /**
         * @brief Constructor for reserving the internal buffer with given amount of data (not bytes!).
         *
         * @param count
         */
        MemoryBlock(std::size_t count);
        ~MemoryBlock();

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
        std::size_t Count() const;

        /**
         * @brief Indicates if the MemoryBlock is null.
         *
         * @return true is null, false otherwise.
         */
        bool IsNull() const;

        /**
         * @brief Indicates if the MemoryBlock is empty (Count = 0, Size = 0, ...).
         *
         * @return true if empty, false otherwise.
         */
        bool IsEmpty() const;

        /**
         * @brief Indicates wether the MemoryBlock is null or empty.
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

        MemoryBlock<T> &operator=(const MemoryBlock<T> &input);
        MemoryBlock<T> &operator=(MemoryBlock<T> &&input);

        void CopyFrom(const std::basic_string_view<T> &input);
        void CopyFrom(const MemoryBlock<T> &input);

    protected:
        std::size_t m_Size = 0;
        std::size_t m_Count = 0;

        T *m_Data = nullptr;
    };

    template <typename T>
    MemoryBlock<T>::MemoryBlock(nullptr_t)
        : m_Data(nullptr), m_Size(0), m_Count(0)
    {
    }

    template <typename T>
    MemoryBlock<T>::MemoryBlock(const MemoryBlock<T> &input)
    {
        delete[] m_Data;
        *this = input;
    }

    template <typename T>
    MemoryBlock<T>::MemoryBlock(MemoryBlock<T> &&input)
        : m_Data(nullptr), m_Size(0), m_Count(0)
    {
        *this = std::move(input);
    }

    template <typename T>
    MemoryBlock<T>::MemoryBlock(std::size_t count)
        : m_Count(count), m_Size(count * sizeof(T))
    {
        m_Data = new T[m_Size];
    }

    template <typename T>
    MemoryBlock<T>::~MemoryBlock()
    {
        if (m_Data == nullptr)
            return;
        delete[] m_Data;
        m_Data = nullptr;
    }

    template <typename T>
    bool MemoryBlock<T>::IsNull() const
    {
        return m_Data == nullptr;
    }

    template <typename T>
    bool MemoryBlock<T>::IsEmpty() const
    {
        return m_Count == 0;
    }

    template <typename T>
    bool MemoryBlock<T>::IsNullOrEmpty() const
    {
        return IsNull() || IsEmpty();
    }

    template <typename T>
    T *MemoryBlock<T>::Data() const
    {
        return m_Data;
    }

    template <typename T>
    const T *MemoryBlock<T>::Data()
    {
        return m_Data;
    }

    template <typename T>
    MemoryBlock<T>::operator T *() const
    {
        return m_Data;
    }

    template <typename T>
    MemoryBlock<T>::operator const T *()
    {
        return m_Data;
    }

    template <typename T>
    T &MemoryBlock<T>::operator[](std::size_t index) const
    {
        if (index >= m_Count)
            throw ArgumentOutOfRangeException("index");
        return m_Data[index];
    }

    template <typename T>
    const T &MemoryBlock<T>::operator[](std::size_t index)
    {
        if (index >= m_Count)
            throw ArgumentOutOfRangeException("index");
        return m_Data[index];
    }

    template <typename T>
    std::size_t MemoryBlock<T>::Size() const
    {
        return m_Size;
    }

    template <typename T>
    std::size_t MemoryBlock<T>::Count() const
    {
        return m_Count;
    }

    template <typename T>
    void MemoryBlock<T>::CopyFrom(const std::basic_string_view<T> &input)
    {
        if (input.length() > m_Count)
            throw ArgumentOutOfRangeException("input.length()");

        std::memcpy(m_Data, input.data(), input.length() * sizeof(T));
    }

    template <typename T>
    void MemoryBlock<T>::CopyFrom(const MemoryBlock<T> &input)
    {
        if (input.Count() > m_Count)
            throw ArgumentOutOfRangeException("input.Count()");

        std::memcpy(m_Data, input.Data(), input.Size());
    }

    template <typename T>
    MemoryBlock<T> &MemoryBlock<T>::operator=(const MemoryBlock<T> &input)
    {
        m_Size = input.m_Size;
        m_Data = new T[m_Size];
        m_Count = input.m_Count;
        CopyFrom(input);
        return *this;
    }

    template <typename T>
    MemoryBlock<T> &MemoryBlock<T>::operator=(MemoryBlock<T> &&input)
    {
        delete[] m_Data;
        m_Size = 0;
        m_Count = 0;

        std::swap(m_Data, input.m_Data);
        std::swap(m_Count, input.m_Count);
        std::swap(m_Size, input.m_Size);

        return *this;
    }
} // namespace Borg
