/*!
 * \file daemon.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include "daemon.hpp"
#include <QtCore/QDebug>
#include <QObject>

Daemon::Daemon(int & argc, char ** argv,  SettingsManager *settings, Logger *LOG) :QCoreApplication(argc, argv){
    this->settings = settings;
    this->LOG = LOG;
    this->server   = new LocalSocketIpcServer(settings->getDaemonName(), this);
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
    QString result = tr("ewapp start\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}


QString Daemon::handleStop(QStringList appsList){
    QString result = tr("ewapp stop\n");
    if(appsList.isEmpty())
        this->isRunning = false;
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

QString Daemon::handleRestart(QStringList appsList){
    QString result = tr("ewapp restart\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}

QString Daemon::handleReload(QStringList appsList){
    QString result = tr("ewapp reload\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}

QString Daemon::handleState(QStringList appsList){
    QString result = tr("ewapp state\n");
    QStringList apps = this->settings->getAppsNames();
    foreach(QString app,appsList){
        if(apps.contains(app)){
            result += app;
        }
    }
    return result;
}

void Daemon::handleCommand(ClientResponse *response){
    LOG->info(tr("New message")+response->getMessage());
    this->args = response->getMessage().split(",", QString::SkipEmptyParts);
    response->sendResponse(this->handleNewArgs());

    if(!this->isRunning){
        this->quit();
    }
}

QString Daemon::displayUsage(){
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

