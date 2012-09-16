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

#include "commandargumenthandler.hpp"

using namespace dns;

CommandArgumentHandler::CommandArgumentHandler(Daemon *daemon) :QObject(daemon){
    this->_daemon = daemon;
}

QString CommandArgumentHandler::handleStart(QStringList appsList){
    QString result = tr("ewapp start\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}


QString CommandArgumentHandler::handleStop(QStringList appsList){
    QString result = tr("ewapp stop\n");
    if(appsList.isEmpty())
        this->_daemon->stop();
    else{
        QStringList apps = this->settings->getAppsNames();
        foreach(QString app,appsList){
            if(apps.contains(app)){
                result += app;
            }
        }
    }
    return result;
}

QString CommandArgumentHandler::handleRestart(QStringList appsList){
    QString result = tr("ewapp restart\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}

QString CommandArgumentHandler::handleReload(QStringList appsList){
    QString result = tr("ewapp reload\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}

QString CommandArgumentHandler::handleState(QStringList appsList){
    QString result = tr("ewapp state\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}



QString CommandArgumentHandler::displayUsage(){
    return tr("usage : ewo-app [action] [params]\n")
            + tr("  action :\n")
            + tr("    start  : start the daemon\n")
            + tr("    stop   : stop the daemon\n")
            + tr("    reload : reload applications\n")
            + tr("    state  : give state of applications on the daemon\n")
            + tr("      option --json send result in json format\n")
            + tr("  params : list of applications\n")
            + tr("           if there is no param all applications are impacted by the action\n");
}
