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
        Ref<IString> m_Impl;
    };
}