#pragma once
#include "Borg/Exception.h"

namespace Borg
{
    template <typename T>
    class MemoryBlock final
    {
    public:
        MemoryBlock(std::size_t count);
        ~MemoryBlock();

        std::size_t SizeInBytes() const;
        std::size_t Count() const;

        T *Data() const;
        T& operator[](std::size_t index);

    private:
        std::size_t m_SizeInBytes;
        std::size_t m_Count;

        T *m_Data;
    };

    template <typename T>
    MemoryBlock<T>::MemoryBlock(std::size_t count)
        :m_Count(count), m_SizeInBytes(count * sizeof(T))
    {
        m_Data = new wchar_t[m_SizeInBytes];
    }

    template <typename T>
    MemoryBlock<T>::~MemoryBlock()
    {
        delete[] m_Data;
    }

    template <typename T>
    T *MemoryBlock<T>::Data() const
    {
        return m_Data;
    }

    template <typename T>
    T& MemoryBlock<T>::operator[](std::size_t index)
    {
        if(index >= m_Count)
            throw ArgumentOutOfRangeException("index");
        return m_Data[index];
    }

    template <typename T>
    std::size_t MemoryBlock<T>::SizeInBytes() const
    {
        return m_SizeInBytes;
    }

    template <typename T>
    std::size_t MemoryBlock<T>::Count() const
    {
        return m_Count;
    }
} // namespace Borg
