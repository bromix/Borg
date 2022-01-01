#pragma once
#include "AbstractStringBuffer.h"

namespace Borg
{
    class CharBuffer : public AbstractStringBuffer<char>
    {
    public:
        CharBuffer(const CharBuffer &input) : AbstractStringBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }

        CharBuffer(std::size_t length) : AbstractStringBuffer<char>(length) {}

        CharBuffer(std::string_view input) : AbstractStringBuffer<char>(input)
        {
            m_Data = m_Ptr;
        }

        Ref<IStringBuffer> Clone() const override
        {
            return CreateRef<CharBuffer>(*this);
        }

    private:
        char *m_Data;
    };
}