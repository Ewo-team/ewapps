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

#include "controller.hpp"
#include "localsocketipcclient.hpp"
#include <iostream>

Controller::Controller(int &argc, char **argv, SettingsManager *settings) : QCoreApplication(argc, argv){
    this->settings = settings;
    //On commence à 1 pour ne pas s'embêter avec le nom de l'appli
   for(int i = 1; i < argc; ++i){
       this->args.append(argv[i]);
   }

}

int Controller::run(){
    LocalSocketIpcClient client(QString(this->settings->getDaemonName()),this);


    connect(&client, SIGNAL(serverResponse(QString)), this, SLOT(displayResponse(QString)));
    QString message = "";
    QStringList::Iterator  it = this->args.begin(), end = this->args.end();
    while(it != end){
        if(message.size() > 0){
            message += ',';
        }
        message += *(it);
        ++it;
    }

    client.send_MessageToServer(message);

    return this->exec();
}

void Controller::displayResponse(QString message){
    std::cout << message.toStdString() << std::endl;
    this->quit();
}
