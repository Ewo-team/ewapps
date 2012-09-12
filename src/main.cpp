/*!
 * \file main.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include <QSettings>
#include <iostream>
#include "settingsmanager.hpp"



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

    return EXIT_SUCCESS;
}
