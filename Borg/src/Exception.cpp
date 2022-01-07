#include "Borg/Exception.h"
#include "Borg/String.h"

namespace Borg
{
    Exception::Exception() {}

    Exception::Exception(const String &message)
        : std::exception(), m_Message(message), m_What(message)
    {
    }

    const char *Exception::what() const noexcept
    {
        return m_What.c_str();
    }

    String Exception::Message() const
    {
        return m_Message;
    }

    // =============================
    // ===== ArgumentException =====
    // =============================

    String ArgumentException::ParamName() const
    {
        return m_ParamName;
    }

}