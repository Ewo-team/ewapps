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

#include "daemonize.hpp"

QString lockFilePathGlob;

bool daemonIsRunning(QString lockFilePath){
    lockFilePathGlob = lockFilePath;
    QFile lockFile(lockFilePathGlob);
    return lockFile.exists();
}

void daemonize(QString directory, Logger *LOG){
    int i;
    char str[10];
    if(getppid()==1)
        return; // déjà un deamon

    /*
    i=fork();
    if (i<0){// fork error
        LOG->error(QObject::tr("Fork error"));
        exit(EXIT_FAILURE);
    }
    if (i>0)// parent /
        exit(EXIT_SUCCESS);


    // Enfant
    setsid(); //Nouveau process group

   // for (i=getdtablesize();i>=0;--i) close(i); // Fermeture de tous les descripteur
   //     i=open("/dev/null",O_RDWR); dup(i); dup(i); // gestion de l'entrée/sortie standard
    */
    umask(027);

    chdir(directory.toStdString().c_str()); //Changement de repertoire d'execution
    sprintf(str,"%d\n",getpid());
    QFile lockFile(lockFilePathGlob);
    lockFile.open(QIODevice::ReadWrite);
    if (lockFile.write(str)<0){
        LOG->error(QObject::tr("Error while opening lock file : ")+QString(lockFilePathGlob));
        exit(EXIT_FAILURE);
    }
    lockFile.close();

    signal(SIGTERM,signal_handler); //Gestion du SIGTERM
    signal(SIGKILL,signal_handler); //Gestion du SIGTERM
    signal(SIGSEGV,signal_handler); //Gestion du SIGSEGV
}

void signal_handler(int sig){
    switch(sig) {
        case SIGTERM:
        case SIGKILL:
        case SIGSEGV:
            freeLockFile();
            exit(EXIT_SUCCESS);
        break;
    }
}

void freeLockFile(){
    QFile lockFile(lockFilePathGlob);
    lockFile.open(QIODevice::ReadWrite);
    lockFile.remove();
}
