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
#include "daemon.hpp"

using namespace dns;

CommandArgumentHandler::CommandArgumentHandler(Daemon *parent, SettingsManager *settings) :QObject(parent){
    this->_daemon = parent;
    this->settings = settings;
}

QString CommandArgumentHandler::handleNewArgs(QStringList args){
    this->args = args;

    //Pas d'argument => action par defaut : start
    if(this->args.size() == 0 )
        return this->handleStart(QStringList());

    //selection de l'action
    QString action(this->args.at(0));
    //Autres arguments
    QStringList otherArgs(this->args);
    otherArgs.removeAt(0);
    if(action == START)
        return this->handleStart(otherArgs);
    if(action == STOP)
        return this->handleStop(otherArgs);
    if(action == RESTART)
        return this->handleRestart(otherArgs);
    if(action == RELOAD)
        return this->handleReload(otherArgs);
    if(action == STATE)
        return this->handleState(otherArgs);
    return  this->displayUsage();
}

bool CommandArgumentHandler::checkArgs(){
    if(this->args.size() == 0 )
        return false;
    QString action(this->args.at(0));
    return action == START      ||
            action == STOP       ||
            action == RESTART    ||
            action == RELOAD     ||
            action == STATE;
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
            + tr("    start  : start the CommandArgumentHandler\n")
            + tr("    stop   : stop the CommandArgumentHandler\n")
            + tr("    reload : reload applications\n")
            + tr("    state  : give state of applications on the CommandArgumentHandler\n")
            + tr("      option --json send result in json format\n")
            + tr("  params : list of applications\n")
            + tr("           if there is no param all applications are impacted by the action\n");
}
