#pragma once
#include <string_view>
#include "Ref.h"

namespace Borg
{
    class IStringBuffer
    {
    public:
        virtual ~IStringBuffer() = default;

        static Ref<IStringBuffer> Create(const char* input);
        static Ref<IStringBuffer> Create(std::string_view input);

        static Ref<IStringBuffer> Create(const wchar_t* input);
        static Ref<IStringBuffer> Create(std::wstring_view input);

        virtual std::size_t Length() const = 0;
        virtual std::size_t ByteLength() const = 0;

        virtual bool IsEmpty() const = 0;

        virtual Ref<IStringBuffer> ToLower() const = 0;
        virtual Ref<IStringBuffer> ToUpper() const = 0;

        virtual Ref<IStringBuffer> Insert(int startIndex, const Ref<IStringBuffer> &value) const = 0;
        virtual Ref<IStringBuffer> Insert(int startIndex, std::string_view value) const = 0;
        virtual Ref<IStringBuffer> Insert(int startIndex, std::wstring_view value) const = 0;

        virtual bool StartsWith(const Ref<IStringBuffer> &text) const = 0;
        virtual bool StartsWith(std::string_view text) const = 0;
        virtual bool StartsWith(std::wstring_view text) const = 0;

        virtual bool EndsWith(const Ref<IStringBuffer> &text) const = 0;
        virtual bool EndsWith(std::string_view text) const = 0;
        virtual bool EndsWith(std::wstring_view text) const = 0;

        virtual int CompareTo(const Ref<IStringBuffer> &rhs) const = 0;
        virtual int CompareTo(std::string_view rhs) const = 0;
        virtual int CompareTo(std::wstring_view rhs) const = 0;

        virtual operator std::string() const = 0;
        virtual operator std::wstring() const = 0;

        virtual Ref<IStringBuffer> Clone() const = 0;
    };
}