#pragma once
#include "../../IString.h"

namespace Borg
{
    class StringImpl : public String::IString
    {
    public:
        StringImpl(std::string_view input);
        virtual bool IsEmpty() const override;
    private:
        std::string m_Data;
    };
}