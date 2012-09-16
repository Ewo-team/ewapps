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

/*!
 * \file daemon.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include "daemon.hpp"
#include <QtCore/QDebug>
#include <QObject>
#include <websocketpp/websocketpp.hpp>

using namespace dns;

Daemon::Daemon(int & argc, char ** argv,  SettingsManager *settings, Logger *LOG) :QCoreApplication(argc, argv){
    this->settings = settings;
    this->LOG = LOG;
    this->server   = new LocalSocketIpcServer(settings->getDaemonName(), this);
    this->commandArgumentHandler = new CommandArgumentHandler(this);
    this->isRunning = true;

    connect(this->server, SIGNAL(messageReceived(ClientResponse*)), this, SLOT(handleCommand(ClientResponse*)));
}

Daemon::~Daemon(){
    delete this->server;
    LOG->info(tr("ewapp killed"));
}


int Daemon::run(){
    LOG->info(tr("ewapp launched"));
    return this->exec();
}
QString Daemon::handleNewArgs(){
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

void Daemon::stop(){
    this->isRunning = false;
}

bool Daemon::checkArgs(){
    if(this->args.size() == 0 )
        return false;
    QString action(this->args.at(0));
    return action == START      ||
            action == STOP       ||
            action == RESTART    ||
            action == RELOAD     ||
            action == STATE;
}



void Daemon::handleCommand(ClientResponse *response){
    LOG->info(tr("New message")+response->getMessage());
    this->args = response->getMessage().split(",", QString::SkipEmptyParts);
    response->sendResponse(this->handleNewArgs());

    if(!this->isRunning){
        this->quit();
    }
}
