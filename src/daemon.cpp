/*!
 * \file daemon.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include "daemon.hpp"
#include <iostream>
#include<QtCore/QDebug>


Daemon::Daemon(int argc, char *argv[]) : QtSingleCoreApplication(argc, argv){

    for(int i = 0; i < argc; ++i){
        this->args.append(argv[i]);
    }
}

Daemon::~Daemon(){
}


int Daemon::run(){
    if (this->isRunning()){
        //transformation des arguments en QString
        QString message = "";
        int i = 0;
        QStringList::const_iterator constIterator, endIt = this->args.end();
        for (constIterator = this->args.constBegin(); constIterator != endIt;++constIterator){
            //ajout du separateur
            if(i > 1){
                message += ",";
            }
            //on ajoute pas le chemin de l'exe
            if(i > 0){
                message += (*constIterator);
            }
            ++i;
        }
        //envoie du message
        this->sendMessage(message);
        return 0;
    }

    this->handleNewArgs();

    QObject::connect(this, SIGNAL(messageReceived(const QString&)),
                     this, SLOT(handleCommand(const QString&)));
    return this->exec();
}


void Daemon::handleNewArgs(){
    for(int i = 0; i < this->args.size();++i){
        std::cout << this->args.at(i).toStdString() << std::endl;
    }

    QStringList::const_iterator constIterator, endIt = this->args.end();
    for (constIterator = this->args.constBegin(); constIterator != endIt;++constIterator){
       QString arg = (*constIterator);
       if(arg.compare("--stop") == 0){
           std::cout << "arret de l'application" << std::endl;
           this->exit();
       }
    }
    //this->displayUsage();
}


void Daemon::handleCommand(const QString& message){
    this->args = message.split(",", QString::SkipEmptyParts);

    for(int i = 0; i < this->args.size();++i){
        std::cout << this->args.at(i).toStdString() << std::endl;
    }
    this->handleNewArgs();
}



void Daemon::displayUsage(){
    std::cerr << "usage : ewo-app [action]" << std::endl;
    std::cerr << "  action :" << std::endl;
    std::cerr << "    --stop   : stop the daemon " << std::endl;
    std::cerr << "    --reload : reload appications " << std::endl;
    std::cerr << "    --state  : return state of applications " << std::endl;
}
