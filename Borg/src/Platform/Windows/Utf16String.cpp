#include "Utf16String.h"

namespace Borg
{
    std::shared_ptr<String::Impl> String::Impl::Create(std::string_view input)
    {
        return std::make_shared<Utf16String>(input);
    }

    Utf16String::Utf16String(std::string_view input)
        : m_Data(input)
    {
    }
}