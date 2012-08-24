/*!
 * \file daemon.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include "daemon.hpp"
#include <iostream>
#include <QObject>


#ifndef DAEMON_CST
#define DAEMON_CST
//init constantes
const QString Daemon::SERVICE_NAME   = QLatin1String("ewapp-service");
#endif

Daemon::Daemon(int argc, char *argv[]) :QtService<QCoreApplication>(argc, argv, SERVICE_NAME){
    this->setServiceDescription(QObject::tr("Ewo apps service"));
    setServiceFlags(QtServiceBase::CannotBeStopped);
}

Daemon::~Daemon(){
}

void Daemon::start(){

}

void Daemon::stop(){

}

void Daemon::pause(){

}

void Daemon::resume(){

}

void Daemon::processCommand(int code){

}

