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

    class InvalidOperationException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the InvalidOperationException class.
         */
        InvalidOperationException();

        /**
         * @brief Initializes a new instance of the InvalidOperationException class with a specified error message.
         *
         * @param message
         */
        InvalidOperationException(const String &message);
    };

    class InvalidCastException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the InvalidCastException class.
         */
        InvalidCastException();

        /**
         * @brief Initializes a new instance of the InvalidCastException class with a specified error message.
         *
         * @param message
         */
        InvalidCastException(const String &message);
    };

    class NullReferenceException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the NullReferenceException class.
         */
        NullReferenceException();

        /**
         * @brief Initializes a new instance of the NullReferenceException class with a specified error message.
         *
         * @param message
         */
        NullReferenceException(const String &message);
    };

    class NotImplementedException : public Exception
    {
    public:
        /**
         * @brief Initializes a new instance of the NotImplementedException class with default properties.
         */
        NotImplementedException();
        ~NotImplementedException() = default;

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
         * @brief Initializes a new instance of the ArgumentException class.
         */
        ArgumentException();
        ~ArgumentException() = default;

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

    class ArgumentNullException : public ArgumentException
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentNullException class.
         */
        ArgumentNullException();
        ~ArgumentNullException() = default;

        /**
         * @brief Initializes a new instance of the ArgumentNullException class with the name of the parameter that causes this exception.
         *
         * @param paramName
         */
        ArgumentNullException(const String &paramName);

        /**
         * @brief Initializes an instance of the ArgumentNullException class with a specified error message and the name of the parameter that causes this exception.
         *
         * @param paramName
         * @param message
         */
        ArgumentNullException(const String &paramName, const String &message);
    };

    class ArgumentOutOfRangeException : public ArgumentException
    {
    public:
        /**
         * @brief Initializes a new instance of the ArgumentOutOfRangeException class.
         */
        ArgumentOutOfRangeException();
        ~ArgumentOutOfRangeException() = default;

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