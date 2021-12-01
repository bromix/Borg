#pragma once
#include "Borg/String.h"

namespace Borg
{
    class String::Impl
    {
    public:
        virtual ~Impl() = default;

        virtual bool IsEmpty() const = 0;

        static Ref<String::Impl> Create(std::string_view input);
    };
}