#pragma once
#include <memory>
#include <string_view>

namespace Borg
{
    class String final
    {
    public:
        String();
        String(std::nullptr_t);
        String(std::string_view input);

        // Copy constructor and assignment operator.
        String(const String &input);
        String operator=(const String &input);

        // Move constructor and assignment operator.
        String(String &&input);
        String operator=(String &&input);

        bool IsNull() const noexcept;
        bool IsEmpty() const noexcept;

        // Public Impl, so we can define and use an interface internally.
        class Impl;

    private:
        std::shared_ptr<Impl> m_Impl;
    };
}