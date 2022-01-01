#pragma once
#include "AbstractStringBuffer.h"

namespace Borg
{
    class WideCharBuffer final : public AbstractStringBuffer<wchar_t>
    {
    public:
        WideCharBuffer(const WideCharBuffer &input) : AbstractStringBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }
        WideCharBuffer(std::size_t length) : AbstractStringBuffer<wchar_t>(length)
        {
            m_Data = m_Ptr;
        }

        WideCharBuffer(std::wstring_view input) : AbstractStringBuffer<wchar_t>(input)
        {
            m_Data = m_Ptr;
        }

        Ref<IStringBuffer> Clone() const override
        {
            return CreateRef<WideCharBuffer>(*this);
        }

    private:
        wchar_t *m_Data;
    };
}