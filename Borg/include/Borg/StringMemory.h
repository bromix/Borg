#pragma once
#include "Borg/MemoryBlock.h"

namespace Borg
{
    template <typename T>
    class StringMemory : public MemoryBlock<T>
    {
    public:
        StringMemory(nullptr_t) : MemoryBlock<T>(nullptr) {}

        /**
         * @brief Creates a new StringMemory with null-termination.
         *
         * @param count
         */
        StringMemory(std::size_t count) : MemoryBlock<T>(count + 1)
        {
            m_Data[count] = '\0';
        }

        /**
         * @brief Returns the count without the null-termination.
         *
         * @return std::size_t
         */
        std::size_t Count() const
        {
            return m_Count > 0 ? m_Count - 1 : 0;
        }
    };

    using CharMemory = StringMemory<char>;
    using WideCharMemory = StringMemory<wchar_t>;
}