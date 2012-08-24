#include "controller.hpp"
#include <iostream>
#include <QObject>

#ifndef CONTROLLER_CST
#define CONTROLLER_CST
//init constantes

const QString Controller::START   = QLatin1String("start");
const QString Controller::STOP    = QLatin1String("stop");
const QString Controller::RESTART = QLatin1String("restart");
const QString Controller::RELOAD  = QLatin1String("reload");
const QString Controller::STATE   = QLatin1String("state");


const QString Controller::SERVICE_NAME   = QLatin1String("ewapp-service");
#endif


Controller::Controller(int argc, char *argv[]) : QtServiceController (SERVICE_NAME){
    //On commence à 1 pour ne pas s'embêter avec le nom de l'appli
    for(int i = 1; i < argc; ++i){
        this->args.append(argv[i]);
    }
}

Controller::~Controller(){

}

void Controller::run(){
    //Pas d'argument => action par defaut : start
    if(this->args.size() == 0 ){
        this->handleStart(QStringList());
        return;
    }
    //selection de l'action
    QString action(this->args.at(0));
    //Autres arguments
    QStringList otherArgs(this->args);
    otherArgs.removeAt(0);

    if(action == START)
        this->handleStart(otherArgs);
    else if(action == STOP)
        this->handleStop(otherArgs);
    else if(action == RESTART)
        this->handleRestart(otherArgs);
    else if(action == RELOAD)
        this->handleReload(otherArgs);
    else if(action == STATE)
        this->handleState(otherArgs);
    else
        this->displayUsage();
}


void Controller::handleStart(QStringList appsList){
    std::cout << QObject::tr("ewapp start").toStdString() <<std::endl;
}


void Controller::handleStop(QStringList appsList){
    std::cout << QObject::tr("ewapp stop").toStdString() <<std::endl;

}

void Controller::handleRestart(QStringList appsList){
    std::cout << QObject::tr("ewapp restart").toStdString() <<std::endl;

}

void Controller::handleReload(QStringList appsList){
    std::cout << QObject::tr("ewapp reload").toStdString() <<std::endl;

}

QString Controller::handleState(QStringList appsList){
    std::cout << QObject::tr("ewapp state").toStdString() <<std::endl;
    return QString("");
}

void Controller::displayUsage(){
    std::cerr << QObject::tr("usage : ewo-app [action] [params]").toStdString() << std::endl
                  << QObject::tr("  action :").toStdString() << std::endl
                  << QObject::tr("    start  : start the daemon").toStdString() << std::endl
                  << QObject::tr("    stop   : stop the daemon").toStdString() << std::endl
                  << QObject::tr("    reload : reload applications").toStdString() << std::endl
                  << QObject::tr("    state  : give state of applications on the daemon").toStdString() << std::endl
                  << QObject::tr("      option --json send result in json format").toStdString() << std::endl
                  << QObject::tr("  params : list of applications").toStdString() << std::endl
                  << QObject::tr("           if there is no param all applications are impacted by the action").toStdString() << std::endl;
}
