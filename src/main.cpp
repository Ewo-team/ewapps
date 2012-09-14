/*!
 * \file main.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include <QSettings>
#include <iostream>
#include "settingsmanager.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "daemon.hpp"

int daemonize(QString directory);

/*!
 * @brief fonction main
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[]){

    /*Daemon app(argc, argv, settings);
    return app.run();*/
    SettingsManager *settings = new SettingsManager();
    std::cout << settings->getDirectory().toStdString() << std::endl;
    if(daemonize(settings->getDirectory()) == DAEMON){
            Daemon *daemon = new Daemon(argc, argv, settings);
            return daemon->run();
    }
    else{
       std::cout << "controller" << std::endl;
    }
    return EXIT_SUCCESS;
}


int daemonize(QString directory){
    int i,lfp;
    char str[10];
    if(getppid()==1)
        return DAEMON; /* already a daemon */


    i=fork();
    if (i<0)/* fork error */
        exit(1);
    if (i>0)/* parent exits */
        exit(0);


    /* child (daemon) continues */
    setsid(); /* obtain a new process group */

    for (i=getdtablesize();i>=0;--i) close(i); /* close all descriptors */
        i=open("/dev/null",O_RDWR); dup(i); dup(i); /* handle standart I/O */

    umask(027); /* set newly created file permissions */

    chdir(directory.toStdString().c_str()); /* change running directory */

    lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
    if (lfp<0) CONTROLLER; /* can not open */
    if (lockf(lfp,F_TLOCK,0)<0) CONTROLLER; /* can not lock */

    write(lfp,str,strlen(str)); /* record pid to lockfile */


    return DAEMON;
}
