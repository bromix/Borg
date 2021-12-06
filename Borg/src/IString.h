#pragma once
#include "Borg/String.h"

namespace Borg
{
    class String::IString
    {
    public:
        static Ref<IString> Create(std::string_view input);
        static Ref<IString> Create(std::wstring_view input);

        virtual ~IString() = default;

        virtual bool IsEmpty() const = 0;
    };
}