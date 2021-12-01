#include "Utf16String.h"

namespace Borg
{
    Ref<String::Impl> String::Impl::Create(std::string_view input)
    {
        return CreateRef<Utf16String>(input);
    }

    Utf16String::Utf16String(std::string_view input)
        : m_Data(input)
    {
    }

    bool Utf16String::IsEmpty() const
    {
        return m_Data.empty();
    }
}