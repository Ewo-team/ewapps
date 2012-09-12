/*!
 * \file main.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include <QSettings>
#include <iostream>
#include "daemon.hpp"
#include "controller.hpp"
#include "settingsmanager.hpp"



/*!
 * @brief fonction main
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[]){
    SettingsManager *settings = new SettingsManager();
    std::cout << settings->isRunning() << std::endl;
    if(settings->isRunning()){
        Controller app(argc, argv);
        return app.run();
    }
    else{
        try{
            Daemon app(argc, argv, settings);
            return app.run();
        }
        catch(...){
            settings->setRunning(false);
        }
    }
    return 0;
}
