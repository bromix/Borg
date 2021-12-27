#pragma once
#include "Borg.h"

namespace Borg
{
    /**
     * @brief Provides information about, and means to manipulate, the current environment and platform. This class cannot be inherited.
     */
    class Environment final
    {
    public:
        /**
         * @brief Specifies enumerated constants used to retrieve directory paths to system special folders.
         */
        enum class SpecialFolder
        {
            /**
             * @brief The directory that serves as a common repository for application-specific data for the current roaming user.
             */
            ApplicationData,

            /**
             * @brief The directory that serves as a common repository for application-specific data that is used by the current, non-roaming user.
             */
            LocalApplicationData
        };

        Environment() = delete;
        Environment(const Environment &) = delete;
        Environment(Environment &&) = delete;
        Environment operator=(const Environment &) = delete;
        Environment operator=(Environment &&) = delete;

        /**
         * @brief Gets the path to the system special folder that is identified by the specified enumeration.
         *
         * @param specialFolder
         * @return String
         */
        static String GetFolderPath(SpecialFolder specialFolder);

        /**
         * @brief Gets the NetBIOS name of this local computer.
         * 
         * @return String 
         */
        static String MachineName();

        /**
         * @brief Gets the user name of the person who is associated with the current thread.
         * 
         * @return String 
         */
        static String UserName();

        /**
         * @brief Gets the newline string defined for this environment.
         * 
         * @return String 
         */
        static String NewLine();

        /**
         * @brief Gets the command line for this process.
         * 
         * @return String 
         */
        static String CommandLine();
    };
}