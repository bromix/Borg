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

        virtual Ref<IString> ToLower() const = 0;
        virtual Ref<IString> ToUpper() const = 0;
        virtual bool StartsWith(const Ref<IString> &text) const = 0;
        virtual bool EndsWith(const Ref<IString> &text) const = 0;

        virtual bool IsEmpty() const = 0;

        virtual int CompareTo(const Ref<IString> &rhs) const = 0;
    };
}