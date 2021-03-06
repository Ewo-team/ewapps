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

using namespace ewapps;

Daemon::Daemon(int & argc, char ** argv,  SettingsManager *settings, Logger *LOG) :QCoreApplication(argc, argv){
    this->m_settings = settings;
    this->LOG = LOG;
    this->m_server   = new LocalSocketIpcServer(settings->getDaemonName(), this->LOG);
    this->m_commandArgumentHandler = new CommandArgumentHandler(this, settings, LOG);
    this->isRunning = true;

    short port = this->m_settings->getWsPort();
    this->m_ws_server = new WebSocketServer(port, this->LOG);

    connect(this->m_server, SIGNAL(messageReceived(ClientResponse*)), this, SLOT(handleCommand(ClientResponse*)));
    connect(this->m_ws_server,SIGNAL(newConnection(QString,WebSocketConnection*)), this, SLOT(newWsConnection(QString,WebSocketConnection*)));
}

Daemon::~Daemon(){
    delete this->m_server;
    LOG->info(tr("ewapp killed"));
}


int Daemon::run(){
    LOG->info(tr("ewapp launched"));
    this->m_commandArgumentHandler->handleStart(QStringList());
    this->m_ws_server->start();
    return this->exec();
}

void Daemon::stop(){
    this->isRunning = false;
}

void Daemon::setRunManager(RunManager *manager){
    this->m_manager = manager;
}

QString Daemon::loadPlugin(QString name){
    QString msg;
    this->reloadConfig();

    if(this->m_plugins.keys().contains(name)){
        PluginInterface *plugin = this->m_plugins[name];
        if(!plugin->isRunning()){
            this->runPlugin(name);
            return this->logAndReturn(name+tr(" started"));
        }
        return this->logAndReturn(name+tr(" is already running"));
    }

    QMap<QString, QString> apps = this->m_settings->getApps();

    if(apps.keys().contains(name)){
        QPluginLoader loader(apps[name]); // On fait ensuite la même chose que pour un seul plugin.
        if(QObject *newPlugin = loader.instance()){
            this->LOG->info(tr("new PLugin : ") + name);

            PluginInterface *plugin = qobject_cast<PluginInterface*>(newPlugin);
            this->m_plugins.insert(name,  plugin);
            this->m_ws_server->addApp(name, plugin);
            this->runPlugin(name);

            return this->logAndReturn(name+tr(" started"));
        }
        return this->logAndReturn(tr("Unable to load plugin ")+name+tr(" location : ")+apps[name]);
    }
    return this->logAndReturn(name+tr(" is not a valid application"));
}

QString Daemon::stopPlugin(QString name){
    if(this->m_plugins.keys().contains(name)){
        PluginInterface *plugin = this->m_plugins[name];
        if(plugin->isRunning()){
            plugin->quit();
            return this->logAndReturn(name+tr(" stopped"));
        }
        return this->logAndReturn(name+tr(" is not running"));
    }
    return this->logAndReturn(name+tr(" is not a valid application"));
}

QString Daemon::getPluginState(QString name){
    return name;
}

void Daemon::reloadConfig(){
    this->m_settings->reLoadConfig();
}

void Daemon::runPlugin(QString name){
    try{
        if(this->m_plugins[name] != NULL){
            LOG->debug(tr("Run plugin ")+name);
            this->m_plugins[name]->start();
        }
    }
    catch(...){
        LOG->debug(tr("PLugin error"));
    }
}


QString Daemon::logAndReturn(QString msg){
    LOG->info(msg);
    return msg;
}


void Daemon::handleCommand(ClientResponse *response){
    LOG->info(tr("New message : ")+response->getMessage());
    QString message = response->getMessage();
    if(message == NULL || message.size() == 0)
        return;
    //Message Json => à envoyer à la bonne appli
    if(message.at(0) == QChar('[') || message.at(0) == QChar('{')){

    }
    else{
        QStringList args = message.split(",", QString::SkipEmptyParts);
        response->sendResponse(this->m_commandArgumentHandler->handleNewArgs(args));
    }
    if(!this->isRunning){
        this->quit();
    }
}

void Daemon::newWsConnection(QString appName, WebSocketConnection *co){
    if(this->m_plugins.keys().contains(appName)){
        this->m_plugins[appName]->handleNewConnection_intern(co);
    }
}

