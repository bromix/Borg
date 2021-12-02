#include "StringImpl.h"

namespace Borg
{
    Ref<String::IString> String::IString::Create(std::string_view input)
    {
        return CreateRef<StringImpl>(input);
    }

    StringImpl::StringImpl(std::string_view input)
        : m_Data(input)
    {
    }

    bool StringImpl::IsEmpty() const
    {
        return m_Data.empty();
    }
}