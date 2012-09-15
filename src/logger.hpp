////////////////////////////////////////////////////////////
//
// Ewapp
// Copyright (C) 2012 Benjamin Herbomez (benjamin.herbomez@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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

#endif // LOGGER_HPP
