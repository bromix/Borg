#pragma once

namespace Borg
{
    class String
    {
    public:
        String();
        String(std::nullptr_t);

        // Copy constructor and assignment operator.
        String(const String &input);
        String operator=(const String &input);

        // Move constructor and assignment operator.
        String(String &&input);
        String operator=(String &&input);
    };
}