#include "controller.hpp"

Controller::Controller(){

}

Controller::~Controller(){

}



void Controller::handleNewArgs(){

}


void Controller::handleStart(QStringList appsList){

}


void Controller::handleStop(QStringList appsList){

}


void Controller::handleReload(QStringList appsList){

}

QString Controller::handleState(QStringList appsList){
    return new QString("");
}

void Controller::displayUsage(){
    std::cerr << "usage : ewo-app [action] [params]" << std::endl
                  << "  action :" << std::endl
                  << "    start  : start the daemon " << std::endl
                  << "    stop   : stop the daemon " << std::endl
                  << "    reload : reload applications " << std::endl
                  << "    state  : give state of applications on the daemon " << std::endl
                  << "      option --json send result in json format" << std::endl
                  << "  params : list of applications" << std::endl
                  << "           if there is no param all applications are impacted by the action" << std::endl;
}
