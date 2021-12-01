#pragma once
#include "../../StringImpl.h"

namespace Borg
{
    class Utf16String : public String::Impl
    {
    public:
        Utf16String(std::string_view input);
    private:
        std::string m_Data;
    };
}