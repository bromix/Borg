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

    // ===========================
    // ===== FormatException =====
    // ===========================

    FormatException::FormatException() : Exception("FormatException") {}
    FormatException::FormatException(const String &message) : Exception(message) {}

    // =============================
    // ===== ArgumentException =====
    // =============================

    ArgumentException::ArgumentException() : Exception("ArgumentException") {}
    ArgumentException::ArgumentException(const String &message) : Exception(message) {}
    ArgumentException::ArgumentException(const String &message, const String &paramName) : Exception(message), m_ParamName(paramName) {}

    String ArgumentException::ParamName() const
    {
        return m_ParamName;
    }

    // =================================
    // ===== ArgumentNullException =====
    // =================================

    ArgumentNullException::ArgumentNullException() : ArgumentException("ArgumentNullException") {}
    ArgumentNullException::ArgumentNullException(const String &paramName) : ArgumentException(paramName) {}
    ArgumentNullException::ArgumentNullException(const String &paramName, const String &message) : ArgumentException(paramName, message) {}

    // =======================================
    // ===== ArgumentOutOfRangeException =====
    // =======================================

    ArgumentOutOfRangeException::ArgumentOutOfRangeException() : ArgumentException("ArgumentOutOfRangeException") {}
    ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String &paramName)
        : ArgumentOutOfRangeException(paramName, "Argument is out of range")
    {
    }
    ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String &paramName, const String &message)
        : ArgumentException(message, paramName)
    {
    }
}