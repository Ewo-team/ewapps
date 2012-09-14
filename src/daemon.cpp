/*!
 * \file daemon.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include "daemon.hpp"
#include <iostream>
#include <QtCore/QDebug>
#include <QObject>

Daemon::Daemon(int & argc, char ** argv,  SettingsManager *settings) :QCoreApplication(argc, argv){
    this->settings = settings;
    this->server   = new LocalSocketIpcServer(QString(DAEMON_NAME), this);
    this->isRunning = true;

    connect(this->server, SIGNAL(messageReceived(ClientResponse*)), this, SLOT(handleCommand(ClientResponse*)));
}

Daemon::~Daemon(){
    std::cout << "ewapp killed" << std::endl;
}


int Daemon::run(){
    std::cout << QObject::tr("ewapp launched").toStdString() << std::endl;
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

QString Daemon::handleStart(QStringList appsList){
    return QObject::tr("ewapp start\n");
}


QString Daemon::handleStop(QStringList appsList){
    this->isRunning = false;
    return QObject::tr("ewapp stop\n");
}

QString Daemon::handleRestart(QStringList appsList){
    return QObject::tr("ewapp restart\n");
}

QString Daemon::handleReload(QStringList appsList){
    return QObject::tr("ewapp reload\n");
}

QString Daemon::handleState(QStringList appsList){
    return QObject::tr("ewapp state\n");
}

void Daemon::handleCommand(ClientResponse *response){
    this->args = response->getMessage().split(",", QString::SkipEmptyParts);
    response->sendResponse(this->handleNewArgs());

    if(!this->isRunning){
        this->quit();
    }
}

QString Daemon::displayUsage(){
    return QObject::tr("usage : ewo-app [action] [params]\n")
            + QObject::tr("  action :\n")
            + QObject::tr("    start  : start the daemon\n")
            + QObject::tr("    stop   : stop the daemon\n")
            + QObject::tr("    reload : reload applications\n")
            + QObject::tr("    state  : give state of applications on the daemon\n")
            + QObject::tr("      option --json send result in json format\n")
            + QObject::tr("  params : list of applications\n")
            + QObject::tr("           if there is no param all applications are impacted by the action\n");
}

