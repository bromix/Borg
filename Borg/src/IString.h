#pragma once
#include "Borg/Types.h"

namespace Borg
{
    class String::IString
    {
    public:
        static Ref<IString> Create(std::string_view input);
        static Ref<IString> Create(std::wstring_view input);

        virtual ~IString() = default;

        virtual Ref<IString> ToLower() const = 0;
        virtual Ref<IString> ToUpper() const = 0;

        virtual bool IsEmpty() const = 0;

        virtual int CompareTo(const Ref<IString> &rhs) const = 0;
    };
}