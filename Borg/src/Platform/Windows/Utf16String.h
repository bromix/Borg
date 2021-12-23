#pragma once
#include "../../IString.h"

namespace Borg
{
    class Utf16String : public String::IString
    {
    public:
        Utf16String(std::string_view input);
        Utf16String(std::wstring_view input);
        ~Utf16String();

        Ref<IString> CreateCopy() const override;

        Ref<IString> ToLower() const override;
        Ref<IString> ToUpper() const override;
        bool StartsWith(const Ref<IString> &text) const override;
        bool EndsWith(const Ref<IString> &text) const override;
        bool IsEmpty() const override;
        int CompareTo(const Ref<IString> &rhs) const override;
    private:
        void cleanup();
        void prepare(std::size_t length);

        wchar_t *m_Data = nullptr;
        std::size_t m_Length = 0;
    };
}