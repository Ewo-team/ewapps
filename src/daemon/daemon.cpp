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
//#include <websocketpp/websocketpp.hpp>

using namespace dns;

Daemon::Daemon(int & argc, char ** argv,  SettingsManager *settings, Logger *LOG) :QCoreApplication(argc, argv){
    this->settings = settings;
    this->LOG = LOG;
    this->server   = new LocalSocketIpcServer(settings->getDaemonName(), this);
    this->commandArgumentHandler = new CommandArgumentHandler(this, settings);
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


void Daemon::stop(){
    this->isRunning = false;
}


void Daemon::handleCommand(ClientResponse *response){
    LOG->info(tr("New message")+response->getMessage());
    QString message = response->getMessage();
    if(message == null || message.size() == 0)
        return;
    //Message Json => à envoyer à la bonne appli
    if(message.at(0) == "[" || message.at(0) == "{"){

    }
    else{
        QStringList args = message.split(",", QString::SkipEmptyParts);
        response->sendResponse(this->commandArgumentHandler->handleNewArgs(args));
    }
    if(!this->isRunning){
        this->quit();
    }
}
