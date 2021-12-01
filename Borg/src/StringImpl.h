#pragma once
#include "Borg/String.h"

namespace Borg
{
    class String::Impl
    {
    public:
        virtual ~Impl() = default;

        static std::shared_ptr<String::Impl> Create(std::string_view input);
    };
}