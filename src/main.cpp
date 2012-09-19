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

#include "daemon/daemon.hpp"
#include "utils/settingsmanager.hpp"
#include "utils/logger.hpp"
#include "controller.hpp"
#include "utils/daemonize.hpp"
#include <stdexcept>
#include <segvcatch.h>




/*!
 * @brief fonction main
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[]){

    segvcatch::init_segv();
    segvcatch::init_fpe();

    Logger *LOG = new Logger(QString(LOG_DIR)+QString(LOG_FILE), LOG_LVL);

    SettingsManager *settings = new SettingsManager(LOG);
    QString lockFilePath = settings->getLockFile();
    if(!daemonIsRunning(lockFilePath)){
            std::cout << QObject::tr("Daemon started").toStdString() << std::endl;
            daemonize(settings->getDirectory(), LOG);

            dns::Daemon *daemon = new dns::Daemon(argc, argv, settings, LOG);
            int result;
            try{
                result = daemon->run();
            }
            catch(std::exception& e){
                LOG->fatal(e.what());
                delete daemon;

                return EXIT_FAILURE;
            }
            catch(...){
                LOG->fatal(QObject::tr("Error"));
                return EXIT_FAILURE;
            }

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

