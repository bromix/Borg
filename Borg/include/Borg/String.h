#pragma once
#include <memory>
#include <string_view>

namespace Borg
{
    class String
    {
    public:
        class Impl;
        String();
        String(std::nullptr_t);
        String(std::string_view input);

        // Copy constructor and assignment operator.
        String(const String &input);
        String operator=(const String &input);

        // Move constructor and assignment operator.
        String(String &&input);
        String operator=(String &&input);

        bool IsNull() const;

    private:
        std::shared_ptr<Impl> m_Impl;
    };
}