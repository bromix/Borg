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
        String(std::string_view input);
        String(std::wstring_view input);

        // Copy constructor and assignment operator.
        String(const String &input);
        String operator=(const String &input);

        // Move constructor and assignment operator.
        String(String &&input);
        String operator=(String &&input);

        bool operator==(const String& rhs) const noexcept;
        bool operator==(std::string_view rhs) const noexcept;
        bool operator==(std::wstring_view rhs) const noexcept;

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

    bool operator==(const std::string_view &lhs, const String &rhs);
    bool operator==(const std::wstring_view &lhs, const String &rhs);
}