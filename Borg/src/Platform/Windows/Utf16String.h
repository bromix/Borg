#pragma once
#include "../../IString.h"

namespace Borg
{
    class Utf16String : public String::IString
    {
    public:
        /**
         * @brief Construct a new Utf 16 String with a prepared buffer length (* sizof(wchar_t))
         *
         * @param length
         */
        Utf16String(std::size_t length);
        Utf16String(std::string_view input);
        Utf16String(std::wstring_view input);
        ~Utf16String();

        Ref<IString> CreateCopy() const override;

        std::size_t Length() const override;

        Ref<IString> ToLower() const override;
        Ref<IString> ToUpper() const override;

        Ref<IString> Insert(int startIndex, const Ref<IString> &value) const override;
        Ref<IString> Insert(int startIndex, std::string_view value) const override;
        Ref<IString> Insert(int startIndex, std::wstring_view value) const override;

        bool StartsWith(const Ref<IString> &text) const override;
        bool StartsWith(std::string_view text) const override;
        bool StartsWith(std::wstring_view text) const override;

        bool EndsWith(const Ref<IString> &text) const override;
        bool EndsWith(std::string_view text) const override;
        bool EndsWith(std::wstring_view text) const override;

        bool IsEmpty() const override;

        int CompareTo(const Ref<IString> &rhs) const override;
        int CompareTo(std::string_view rhs) const override;
        int CompareTo(std::wstring_view rhs) const override;

    private:
        void reset();
        void prepare(std::size_t length);

        wchar_t *m_Data = nullptr;
        std::size_t m_Length = 0;
    };
}