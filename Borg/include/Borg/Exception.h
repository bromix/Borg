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
    };

    class NotImplementedException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the NotImplementedException class with default properties.
         */
        NotImplementedException();

        /**
         * @brief Initializes a new instance of the NotImplementedException class with a specified error message.
         *
         * @param message
         */
        NotImplementedException(const String &message);
    };

    class ArgumentException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentException class with a specified error message.
         *
         * @param message
         */
        ArgumentException(const String &message);

        /**
         * @brief Initializes a new instance of the ArgumentException class with a specified error message and the name of the parameter that causes this exception.
         *
         * @param message
         * @param paramName
         */
        ArgumentException(const String &message, const String &paramName);

        /**
         * @brief Gets the name of the parameter that causes this exception.
         *
         * @return String
         */
        String ParamName() const;

    private:
        String m_ParamName;
    };

    class ArgumentOutOfRangeException : public ArgumentException
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentOutOfRangeException class with the name of the parameter that causes this exception.
         *
         * @param paramName
         */
        ArgumentOutOfRangeException(const String &paramName);

        /**
         * @brief Initializes a new instance of the ArgumentOutOfRangeException class with the name of the parameter that causes this exception and a specified error message.
         *
         * @param paramName
         * @param message
         */
        ArgumentOutOfRangeException(const String &paramName, const String &message);
    };
}