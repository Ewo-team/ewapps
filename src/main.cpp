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
#include "daemon.hpp"
#include "controller.hpp"
#include "logger.hpp"

bool daemonIsRunning();
void daemonize(QString directory, Logger *LOG );
void signal_handler(int sig);
void freeLockFile();

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

    if(!daemonIsRunning()){
            std::cout << QObject::tr("Daemon started").toStdString() << std::endl;
            daemonize(settings->getDirectory(), LOG);
            Daemon *daemon = new Daemon(argc, argv, settings, LOG);

            int result = daemon->run();
            freeLockFile();
            delete daemon;
            return result;
    }
    else{
            Controller *controller = new Controller(argc, argv);
            return controller->run();
    }
    return EXIT_SUCCESS;
}

bool daemonIsRunning(){
    QFile lockFile(LOCK_FILE);
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
    QFile lockFile(LOCK_FILE);
    lockFile.open(QIODevice::ReadWrite);
    if (lockFile.write(str)<0){
        LOG->error(QObject::tr("Error while opening lock file : ")+QString(LOCK_FILE));
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
    QFile lockFile(LOCK_FILE);
    lockFile.open(QIODevice::ReadWrite);
    lockFile.remove();
}
