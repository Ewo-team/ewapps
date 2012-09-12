#include "controller.hpp"
#include "localsocketipcclient.hpp"
#include <iostream>

Controller::Controller(int &argc, char **argv) : QCoreApplication(argc, argv){

    //On commence � 1 pour ne pas s'emb�ter avec le nom de l'appli
   for(int i = 1; i < argc; ++i){
       this->args.append(argv[i]);
   }

}

int Controller::run(){
    LocalSocketIpcClient client(QString(DAEMON_NAME),this);


    connect(&client, SIGNAL(serverResponse(QString)), this, SLOT(displayResponse(QString)));

    std::cout << DAEMON_NAME << std::endl;
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
    std::cout << "message sended" << std::endl;
    return this->exec();
}

void Controller::displayResponse(QString message){
    std::cout << message.toStdString() << std::endl;
    this->quit();
}
