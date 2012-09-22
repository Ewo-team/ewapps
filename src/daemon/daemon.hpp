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
 * \file daemon.hpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <QCoreApplication>
#include <QStringList>
#include "../localSocket/localsocketipcserver.hpp"
#include "../common/utils/settingsmanager.hpp"
#include "../common/utils/logger.hpp"
#include "../common/plugin/plugin.hpp"
#include "commandargumenthandler.hpp"
#include "../wsSocket/websocketserver.hpp"

class RunManager;

namespace ewapps{
    /*!
     * @brief classe principale
     * C'est une classe qui va gérer le cycle de vie du daemon
     */
    class Daemon : public QCoreApplication{
            Q_OBJECT

        friend class CommandArgumentHandler;

        protected:
            RunManager *m_manager;
            Logger *LOG;
            SettingsManager *m_settings;
            CommandArgumentHandler *m_commandArgumentHandler;
            LocalSocketIpcServer *m_server;
            bool isRunning;

            QMap<QString, PluginInterface*> m_plugins;

            WebSocketServer *m_ws_server;
        public:


            /**
             * @brief constructeur
             *
             * @param argc
             * @param argv
             * @param settings settings manager
             * @param LOG logger
             */
            explicit Daemon(int & argc, char ** argv, SettingsManager *m_settings, Logger *LOG);


            /*!
             * @brief destructeur
             *
             */
            ~Daemon();

            /*!
             * @brief Arrête le daemon
             *
             */
            void stop();

            /*!
             * @brief set run manager
             */
            void setRunManager(RunManager *manager);

            QString loadPlugin(QString name);

            QString stopPlugin(QString name);

            QString getPluginState(QString name);

            /*!
             * @brief run the application
             *
             * @return int le status de retour de l'application
             */
            int run();

        protected:

            void reloadConfig();
            void runPlugin(QString name);
            QString logAndReturn(QString msg);
        public slots:

            /*!
             * @brief gestion des messages reçus
             *
             * @param response
             */
            void handleCommand(ClientResponse *response);

            void newWsConnection(QString appName, WebSocketConnection *co);
    };
}
#endif // DAEMON_HPP
