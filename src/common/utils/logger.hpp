//////////////////////////////////////////////////////////////////////////
//
//             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// Version 2, December 2004
//
// Copyright (C) 2012 Benjamin Herbomez (benjamin.herbomez@gmail.com)
//
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
// 0. You just DO WHAT THE FUCK YOU WANT TO.
//
//////////////////////////////////////////////////////////////////////////

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QString>

enum LogLvl{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

namespace ewapps{
    /*!
     * @brief classe de log
     */
    class Logger{
        private:
            QString logFile;
            LogLvl lvl;
        public:
            Logger(QString filePath, LogLvl lvl);

            void log(QString message, LogLvl lvl);
            void debug(QString message);
            void info(QString message);
            void warning(QString message);
            void error(QString message);
            void fatal(QString message);
    };
}
#endif // LOGGER_HPP
