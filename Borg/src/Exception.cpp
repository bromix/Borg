#include "Borg/Exception.h"

namespace Borg
{
    Exception::Exception(const String &message)
        : m_Message(message)
    {
    }

    String Exception::Message() const
    {
        return m_Message;
    }

    ArgumentException::ArgumentException(const String &message)
        : Exception(message)
    {
    }

    ArgumentException::ArgumentException(const String &message, const String &paramName)
        : Exception(message), m_ParamName(paramName)
    {
    }

    String ArgumentException::ParamName() const
    {
        return m_ParamName;
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String &paramName)
        : ArgumentOutOfRangeException(paramName, "Argument is out of range")
    {
    }

    ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String &paramName, const String &message)
        : ArgumentException(message, paramName)
    {
    }
}