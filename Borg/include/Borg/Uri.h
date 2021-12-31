#pragma once
#include "String.h"

namespace Borg
{
    class Uri final
    {
    public:
        /**
         * @brief Initializes a new instance of the Uri class with the specified URI.
         *
         * @param uri
         */
        Uri(const String &uri);
        ~Uri() = default;

        /**
         * @brief Gets the scheme name for this URI.
         *
         * @return String
         */
        String Scheme() const;

        /**
         * @brief Gets the host component of this instance.
         *
         * @return String
         */
        String Host() const;

        /**
         * @brief Gets the port number of this URI.
         *
         * @return int
         */
        int Port() const;

        /**
         * @brief Gets the path of this URI.
         *
         * @return String
         */
        String Path() const;

        /**
         * @brief Gets any query information included in the specified URI.
         * 
         * @return String 
         */
        String Query() const;

        /**
         * @brief Determines whether this URI has a particular scheme.
         * @remark The compare is case-insensitive.
         * 
         * @param scheme 
         * @return true 
         * @return false 
         */
        bool IsScheme(const String &scheme) const;

    private:
        String m_Scheme;
        String m_Host;
        int m_Port;
        String m_Path;
        String m_Query;
    };
}