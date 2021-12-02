#pragma once
#include "Borg/String.h"

namespace Borg
{
    class String::IString
    {
    public:
        virtual ~IString() = default;

        virtual bool IsEmpty() const = 0;

        static Ref<String::IString> Create(std::string_view input);
    };
}