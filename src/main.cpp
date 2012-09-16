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
 * \file main.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include <QSettings>
#include <QFile>
#include <iostream>
#include "settingsmanager.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "daemon/daemon.hpp"
#include "controller.hpp"
#include "logger.hpp"


bool daemonIsRunning();
void daemonize(QString directory,Logger *LOG );
void signal_handler(int sig);
void freeLockFile();

QString lockFilePath;

/*!
 * @brief fonction main
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[]){


    Logger *LOG = new Logger(QString(LOG_DIR)+QString(LOG_FILE), LOG_LVL);

    SettingsManager *settings = new SettingsManager(LOG);
    lockFilePath = settings->getLockFile();
    if(!daemonIsRunning()){
            std::cout << QObject::tr("Daemon started").toStdString() << std::endl;
            daemonize(settings->getDirectory(), LOG);
            dns::Daemon *daemon = new dns::Daemon(argc, argv, settings, LOG);

            int result = daemon->run();
            freeLockFile();
            delete daemon;
            return result;
    }
    else{
            Controller *controller = new Controller(argc, argv, settings);
            return controller->run();
    }
    return EXIT_SUCCESS;
}

bool daemonIsRunning(){
    QFile lockFile(lockFilePath);
    return lockFile.exists();
}

void daemonize(QString directory, Logger *LOG){
    int i;
    char str[10];
    if(getppid()==1)
        return; // déjà un deamon


    i=fork();
    if (i<0)/* fork error */{
        LOG->error(QObject::tr("Fork error"));
        exit(EXIT_FAILURE);
    }
    if (i>0)/* parent */
        exit(EXIT_SUCCESS);


    /* Enfant */
    setsid(); //Nouveau process group

    for (i=getdtablesize();i>=0;--i) close(i); // Fermeture de tous les descripteur
        i=open("/dev/null",O_RDWR); dup(i); dup(i); // gestion de l'entrée/sortie standard

    umask(027);

    chdir(directory.toStdString().c_str()); //Changement de repertoire d'execution
    sprintf(str,"%d\n",getpid());
    QFile lockFile(lockFilePath);
    lockFile.open(QIODevice::ReadWrite);
    if (lockFile.write(str)<0){
        LOG->error(QObject::tr("Error while opening lock file : ")+QString(lockFilePath));
        exit(EXIT_FAILURE);
    }
    lockFile.close();

    signal(SIGTERM,signal_handler); //Gestion du SIGTERM
    signal(SIGKILL,signal_handler); //Gestion du SIGTERM
}

void signal_handler(int sig){
    switch(sig) {
        case SIGTERM:
        case SIGKILL:
            freeLockFile();
            exit(EXIT_SUCCESS);
        break;
    }
}

void freeLockFile(){
    QFile lockFile(lockFilePath);
    lockFile.open(QIODevice::ReadWrite);
    lockFile.remove();
}
