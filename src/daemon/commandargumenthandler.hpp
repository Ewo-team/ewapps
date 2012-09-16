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

#ifndef COMMANDARGUMENTHANDLER_HPP
#define COMMANDARGUMENTHANDLER_HPP

#include <QObject>
#include <QStringList>
#include "../utils/settingsmanager.hpp"

namespace dns{

    class Daemon;

    class CommandArgumentHandler : public QObject{
            Q_OBJECT

        private:
            Daemon *_daemon;
            SettingsManager *settings;
            QStringList     args;
        public:
            explicit CommandArgumentHandler(Daemon *parent, SettingsManager *settings);

            /*!
             * @brief fonction appelée si le daemon est déjà lancé
             *
             * @param args arugments à parser
             * @return int
             */
            QString handleNewArgs(QStringList args);

        protected:

            /**
             * @brief vérifie si les arguments sont valides
             *
             * @return bool
             */
            bool checkArgs();

            /*!
             * @brief gestion de la méthode start
             *
             * @param appsList liste des applications à demmarer
             */
            QString handleStart(QStringList appsList);

            /*!
             * @brief gestion du stop d'applis
             *
             * @param appsList liste des applications à stoper
             */
            QString handleStop(QStringList appsList);

            /*!
             * @brief gestion de la méthode restart
             *
             * @param appsList liste des applications à demmarer
             */
            QString handleRestart(QStringList appsList);

            /*!
                     * @brief gestion des applications à recharger
                     *
                     * @param appsList liste des applications à recharger
                     */
            QString handleReload(QStringList appsList);


            /*!
             * @brief gestion de la demande d'état
             *
             * @param appsList liste des applications dont on veut l'état
             * @return QString état des applications
             */
            QString handleState(QStringList appsList);


            /*!
             * @brief affiche l'utilisation de la commande
             *
             */
            QString displayUsage();
        signals:

        public slots:

    };
}
#endif // COMMANDARGUMENTHANDLER_HPP
