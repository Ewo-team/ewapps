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


#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QCoreApplication>
#include <QStringList>
#include "common/utils/settingsmanager.hpp"

namespace ewapps{
    /*!
     * @brief controle du daemon
     * Permet d'envoyer des commandes au daemon
     */
    class Controller : public QCoreApplication{
            Q_OBJECT

        protected:
            QStringList args;
            SettingsManager *settings;

        public:
            explicit Controller(int &argc, char **argv, SettingsManager *settings);


        signals:

        public slots:
            int run();
            void displayResponse(QString);

    };
}
#endif // CONTROLLER_HPP
