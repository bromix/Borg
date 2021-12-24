#pragma once
#include "Borg/Types.h"

namespace Borg
{
    class String final
    {
    public:
        String();
        ~String() = default;
        String(std::nullptr_t);
        String(const char *input);
        String(const wchar_t *input);
        String(const std::string& input);
        String(const std::wstring& input);

        // Copy constructor and assignment operator.
        String(const String &input);
        String operator=(const String &input);

        // Move constructor and assignment operator.
        String(String &&input);
        String operator=(String &&input);

        bool operator==(const String &rhs) const noexcept;
        bool operator==(const char *rhs) const noexcept;
        bool operator==(const wchar_t *rhs) const noexcept;
        bool operator==(const std::string &rhs) const noexcept;
        bool operator==(const std::wstring &rhs) const noexcept;

        /**
         * @brief Returns a copy of this string converted to lowercase.
         *
         * @return String
         */
        String ToLower() const noexcept;

        /**
         * @brief Returns a copy of this string converted to uppercase.
         *
         * @return String
         */
        String ToUpper() const noexcept;

        /**
         * @brief Determines whether the beginning of this string instance matches the specified string.
         *
         * @param text
         * @return true if value matches the beginning of this string; otherwise, false.
         */
        bool StartsWith(const String &text) const noexcept;
        bool StartsWith(const char* text) const noexcept;
        bool StartsWith(const wchar_t* &text) const noexcept;
        bool StartsWith(const std::string &text) const noexcept;
        bool StartsWith(const std::wstring &text) const noexcept;

        /**
         * @brief Determines whether the end of this string instance matches the specified string.
         *
         * @param text
         * @return true if value matches the end of this instance; otherwise, false.
         */
        bool EndsWith(const String &text) const noexcept;
        bool EndsWith(const char* text) const noexcept;
        bool EndsWith(const wchar_t* &text) const noexcept;
        bool EndsWith(const std::string &text) const noexcept;
        bool EndsWith(const std::wstring &text) const noexcept;

        /**
         * @brief Indicates if the specified string is null.
         *
         * @return true is null, false otherwise.
         */
        bool IsNull() const noexcept;

        /**
         * @brief Indicates if the specified string empty string ("").
         *
         * @return true if empty, false otherwise.
         */
        bool IsEmpty() const noexcept;

        /**
         * @brief Indicates wether the specified string is null or empty string ("").
         *
         * @return true
         * @return false
         */
        bool IsNullOrEmpty() const noexcept;

        class IString;

    private:
        String(const Ref<IString> &input) = delete;
        String operator=(const Ref<IString> &input) = delete;
        String(Ref<IString> &&input);
        String operator=(Ref<IString> &&input) = delete;

        Ref<IString> m_Impl;
    };

    bool operator==(const char *lhs, const String &rhs);
    bool operator==(const wchar_t *lhs, const String &rhs);
}