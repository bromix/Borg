#pragma once
#include "Ref.h"
#include "Encoding.h"
#include <string>

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
        String(const std::string &input);
        String(const std::wstring &input);

        String(const CharBuffer &input);
        String(CharBuffer &&input);
        String(const WideCharBuffer &input);
        String(WideCharBuffer &&input);

        String(const char *input, std::size_t length);
        String(const wchar_t *input, std::size_t length);

        // Copy constructor and assignment operator.
        String(const String &input);
        String operator=(const String &input);

        // Move constructor and assignment operator.
        String(String &&input);
        String operator=(String &&input);

        /**
         * @brief Gets the number of characters in the current String object.
         *
         * @return std::size_t
         */
        std::size_t Length() const;

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
         * @brief Returns a new string in which a specified string is inserted at a specified index position in this instance.
         *
         * @param startIndex
         * @param value
         * @return String
         */
        String Insert(int startIndex, const String &value) const;
        String Insert(int startIndex, const char *value) const;
        String Insert(int startIndex, const wchar_t *value) const;
        String Insert(int startIndex, const std::string &value) const;
        String Insert(int startIndex, const std::wstring &value) const;

        String Append(const String &value) const;
        String Append(const char *value) const;
        String Append(const wchar_t *value) const;
        String Append(const std::string &value) const;
        String Append(const std::wstring &value) const;

        String Prepend(const String &value) const;
        String Prepend(const char *value) const;
        String Prepend(const wchar_t *value) const;
        String Prepend(const std::string &value) const;
        String Prepend(const std::wstring &value) const;

        /**
         * @brief Determines whether the beginning of this string instance matches the specified string.
         *
         * @param text
         * @return true if value matches the beginning of this string; otherwise, false.
         */
        bool StartsWith(const String &text) const;
        bool StartsWith(const char *text) const;
        bool StartsWith(const wchar_t *text) const;
        bool StartsWith(const std::string &text) const;
        bool StartsWith(const std::wstring &text) const;

        /**
         * @brief Determines whether the end of this string instance matches the specified string.
         *
         * @param text
         * @return true if value matches the end of this instance; otherwise, false.
         */
        bool EndsWith(const String &text) const;
        bool EndsWith(const char *text) const;
        bool EndsWith(const wchar_t *text) const;
        bool EndsWith(const std::string &text) const;
        bool EndsWith(const std::wstring &text) const;

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

        String operator+(const String &rhs) const;
        String operator+(const char *rhs) const;
        String operator+(const wchar_t *rhs) const;
        String operator+(const std::string &rhs) const;
        String operator+(const std::wstring &rhs) const;

        bool operator==(const String &rhs) const;
        bool operator==(const char *rhs) const;
        bool operator==(const wchar_t *rhs) const;
        bool operator==(const std::string &rhs) const;
        bool operator==(const std::wstring &rhs) const;

        bool operator!=(const String &rhs) const;
        bool operator!=(const char *rhs) const;
        bool operator!=(const wchar_t *rhs) const;
        bool operator!=(const std::string &rhs) const;
        bool operator!=(const std::wstring &rhs) const;

        bool operator<(const String &rhs) const;
        bool operator<(const char *rhs) const;
        bool operator<(const wchar_t *rhs) const;
        bool operator<(const std::string &rhs) const;
        bool operator<(const std::wstring &rhs) const;

        bool operator>(const String &rhs) const;
        bool operator>(const char *rhs) const;
        bool operator>(const wchar_t *rhs) const;
        bool operator>(const std::string &rhs) const;
        bool operator>(const std::wstring &rhs) const;

        /**
         * @brief Indicates wether the specified string is NOT null and NOT empty string ("").
         *
         * @return true if the string is NOT null and NOT empty, false otherwise.
         */
        explicit operator bool() const;

        /**
         * @brief Cast operator for std::string. This will create a copy of the string.
         *
         * @return std::string
         */
        operator std::string() const;

        /**
         * @brief Cast operator for std::wstring. This will create a copy of the string.
         *
         * @return std::wstring
         */
        operator std::wstring() const;

        Encoding::Default GetBuffer() const;

    private:
        Encoding::DefaultChar *m_Data;
        Encoding::Default m_Buffer = nullptr;
    };

    String operator+(const char *lhs, const String &rhs);
    String operator+(const wchar_t *lhs, const String &rhs);
    String operator+(const std::string &lhs, const String &rhs);
    String operator+(const std::wstring &lhs, const String &rhs);

    bool operator==(const char *lhs, const String &rhs);
    bool operator==(const wchar_t *lhs, const String &rhs);
    bool operator==(const std::string &lhs, const String &rhs);
    bool operator==(const std::wstring &lhs, const String &rhs);

    bool operator!=(const char *lhs, const String &rhs);
    bool operator!=(const wchar_t *lhs, const String &rhs);
    bool operator!=(const std::string &lhs, const String &rhs);
    bool operator!=(const std::wstring &lhs, const String &rhs);
}