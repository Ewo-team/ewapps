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

#include "logger.hpp"
#include <QFile>
#include <QTime>
#include <QDate>

using namespace ewapps;

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
