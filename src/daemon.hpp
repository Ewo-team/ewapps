/*!
 * \file daemon.hpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <QCoreApplication>
#include <QStringList>
#include "settingsmanager.hpp"
#include "localsocketipcserver.hpp"
#include "logger.hpp"

/*!
 * @brief classe principale
 * C'est une classe qui va gérer le cycle de vie du daemon
 */
class Daemon : public QCoreApplication{
        Q_OBJECT

    protected:
        Logger *LOG;
        QStringList     args;
        SettingsManager *settings;
        LocalSocketIpcServer *server;

        bool isRunning;


    public:


        /**
         * @brief constructeur
         *
         * @param argc
         * @param argv
         * @param LOG : logger
         */
        explicit Daemon(int & argc, char ** argv, SettingsManager *settings, Logger *LOG);


        /*!
         * @brief destructeur
         *
         */
        ~Daemon();

        /*!
         * @brief run the application
         *
         * @return int le status de retour de l'application
         */
        int run();

    protected:

        /*!
         * @brief fonction appelée si le daemon est déjà lancé
         *
         * @return int
         */
        QString handleNewArgs();


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

    public slots:

        /*!
         * @brief gestion des messages reçus
         *
         * @param response
         */
        void handleCommand(ClientResponse *response);
};

#endif // DAEMON_HPP
