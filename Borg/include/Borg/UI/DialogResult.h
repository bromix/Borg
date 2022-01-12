#pragma once

namespace Borg::UI
{
    /**
     * @brief Specifies identifiers to indicate the return value of a dialog box.
     */
    enum class DialogResult
    {
        /**
         * @brief Nothing is returned from the dialog box. This means that the modal dialog continues running.
         */
        None = 0,

        /**
         * @brief The dialog box return value is OK (usually sent from a button labeled OK).
         */
        OK = 1,

        /**
         * @brief The dialog box return value is Cancel (usually sent from a button labeled Cancel).
         */
        Cancel = 2,

        /**
         * @brief The dialog box return value is Abort (usually sent from a button labeled Abort).
         */
        Abort = 3,

        /**
         * @brief The dialog box return value is Retry (usually sent from a button labeled Retry).
         */
        Retry = 4,

        /**
         * @brief The dialog box return value is Ignore (usually sent from a button labeled Ignore).
         */
        Ignore = 5,

        /**
         * @brief The dialog box return value is Yes (usually sent from a button labeled Yes).
         */
        Yes = 6,

        /**
         * @brief The dialog box return value is No (usually sent from a button labeled No).
         */
        No = 7,

        /**
         * @brief The dialog box return value is Try Again (usually sent from a button labeled Try Again).
         */
        TryAgain = 10,

        /**
         * @brief The dialog box return value is Continue (usually sent from a button labeled Continue).
         */
        Continue = 11
    };
}