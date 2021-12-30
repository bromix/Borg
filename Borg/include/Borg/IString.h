#pragma once
#include <string_view>
#include "IStringBuffer.h"

namespace Borg
{
    class IString
    {
    public:
        static Ref<IString> Create(std::string_view input);
        static Ref<IString> Create(std::wstring_view input);

        virtual ~IString() = default;

        virtual Ref<IString> CreateCopy() const = 0;

        virtual std::size_t Length() const = 0;

        virtual bool IsEmpty() const = 0;

        virtual Ref<IString> ToLower() const = 0;
        virtual Ref<IString> ToUpper() const = 0;

        virtual Ref<IString> Insert(int startIndex, const Ref<IString> &value) const = 0;
        virtual Ref<IString> Insert(int startIndex, std::string_view value) const = 0;
        virtual Ref<IString> Insert(int startIndex, std::wstring_view value) const = 0;

        virtual bool StartsWith(const Ref<IString> &text) const = 0;
        virtual bool StartsWith(std::string_view text) const = 0;
        virtual bool StartsWith(std::wstring_view text) const = 0;

        virtual bool EndsWith(const Ref<IString> &text) const = 0;
        virtual bool EndsWith(std::string_view text) const = 0;
        virtual bool EndsWith(std::wstring_view text) const = 0;

        virtual int CompareTo(const Ref<IString> &rhs) const = 0;
        virtual int CompareTo(std::string_view rhs) const = 0;
        virtual int CompareTo(std::wstring_view rhs) const = 0;

        virtual operator std::string() const = 0;
        virtual operator std::wstring() const = 0;

        virtual Ref<IStringBuffer> GetBuffer() const = 0;
    };
}