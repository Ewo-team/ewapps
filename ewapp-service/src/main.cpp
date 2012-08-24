/*!
 * \file main.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */


#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <iostream>
#include "daemon.hpp"


/*!
 * @brief fonction main
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[]){

    #if !defined(Q_WS_WIN)
        // QtService stores service settings in SystemScope, which normally require root privileges.
        // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
        QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
        qWarning(tr("(Example uses dummy settings file: %s/QtSoftware.conf)"), QDir::tempPath().toLatin1().constData());
    #endif

    Daemon app(argc, argv);

    return app.exec();
}
