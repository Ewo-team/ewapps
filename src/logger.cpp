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

#include "logger.hpp"
#include <QFile>
#include <QTime>
#include <QDate>
#include <iostream>

Logger::Logger(QString filePath, LogLvl lvl){
    this->logFile = filePath;
    this->lvl = lvl;
}

void Logger::debug(QString message){
    this->log(message, DEBUG);
}
void Logger::info(QString message){
    this->log(message, INFO);
}
void Logger::warning(QString message){
    this->log(message, WARNING);
}
void Logger::error(QString message){
    this->log(message, DEBUG);
}
void Logger::fatal(QString message){
    this->log(message, DEBUG);
}

void Logger::log(QString message, LogLvl lvl){
    //Log seulement les niveaux supérieurs
    if(lvl < this->lvl)
        return;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QFile file(this->logFile);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QString line = date.toString()+" - "+time.toString()+" : "+message+"\n";
    file.write((const char *)line.toAscii().data());
    file.close();
}
