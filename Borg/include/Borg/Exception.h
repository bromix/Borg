#pragma once
#include <execution>
#include "String.h"

namespace Borg
{
    class Exception : public std::exception
    {
    public:
        /**
         * @brief Initializes a new instance of the Exception class.
         */
        Exception();
        ~Exception() = default;

        const char *what() const noexcept;

        /**
         * @brief Initializes a new instance of the Exception class with a specified error message.
         *
         * @param message
         */
        Exception(const String &message);

        /**
         * @brief Gets a message that describes the current exception.
         *
         * @return String
         */
        String Message() const;

    private:
        String m_Message;
        std::string m_What;
    };

    class FormatException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the FormatException class.
         */
        FormatException() : Exception("FormatException") {}

        /**
         * @brief Initializes a new instance of the FormatException class with a specified error message.
         * @param message
         */
        FormatException(const String &message) : Exception(message) {}
    };

    class NotSupportException : public Exception
    {
    public:
        NotSupportException() : Exception("NotSupportException") {}
        NotSupportException(const String &message) : Exception(message) {}
    };

    class InvalidOperationException : public Exception
    {
    public:
        InvalidOperationException() : Exception("InvalidOperationException") {}
        InvalidOperationException(const String &message) : Exception(message) {}
    };

    class InvalidCastException : public Exception
    {
    public:
        InvalidCastException() : Exception("InvalidCastException") {}
        InvalidCastException(const String &message) : Exception(message) {}
    };

    class NullReferenceException : public Exception
    {
    public:
        NullReferenceException() : Exception("NullReferenceException") {}
        NullReferenceException(const String &message) : Exception(message) {}
    };

    class NotImplementedException : public Exception
    {
    public:
        NotImplementedException() : Exception("NotImplementedException") {}
        NotImplementedException(const String &message) : Exception(message) {}
    };

    class ArgumentException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentException class.
         */
        ArgumentException() : Exception("ArgumentException") {}

        /**
         * @brief Initializes a new instance of the ArgumentException class with a specified error message.
         *
         * @param message
         */
        ArgumentException(const String &message) : Exception(message) {}

        /**
         * @brief Initializes a new instance of the ArgumentException class with a specified error message and the name of the parameter that causes this exception.
         *
         * @param message
         * @param paramName
         */
        ArgumentException(const String &message, const String &paramName) : Exception(message), m_ParamName(paramName) {}

        /**
         * @brief Gets the name of the parameter that causes this exception.
         *
         * @return String
         */
        String ParamName() const;

    private:
        String m_ParamName;
    };

    class ArgumentNullException : public ArgumentException
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentNullException class.
         */
        ArgumentNullException() : ArgumentException("ArgumentNullException") {}

        /**
         * @brief Initializes a new instance of the ArgumentNullException class with the name of the parameter that causes this exception.
         *
         * @param paramName
         */
        ArgumentNullException(const String &paramName) : ArgumentException("ArgumentNullException", paramName) {}

        /**
         * @brief Initializes an instance of the ArgumentNullException class with a specified error message and the name of the parameter that causes this exception.
         *
         * @param paramName
         * @param message
         */
        ArgumentNullException(const String &paramName, const String &message) : ArgumentException(message, paramName) {}
    };

    class ArgumentOutOfRangeException : public ArgumentException
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentOutOfRangeException class.
         */
        ArgumentOutOfRangeException() : ArgumentException("ArgumentOutOfRangeException") {}

        /**
         * @brief Initializes a new instance of the ArgumentOutOfRangeException class with the name of the parameter that causes this exception.
         *
         * @param paramName
         */
        ArgumentOutOfRangeException(const String &paramName) : ArgumentException("ArgumentOutOfRangeException", paramName) {}

        /**
         * @brief Initializes a new instance of the ArgumentOutOfRangeException class with the name of the parameter that causes this exception and a specified error message.
         *
         * @param paramName
         * @param message
         */
        ArgumentOutOfRangeException(const String &paramName, const String &message) : ArgumentException(message, paramName) {}
    };
}