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

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <QThread>
#include <QtPlugin>
#include <QMap>
#include <QUuid>
#include <QtScript>
#include "wsclient.hpp"
#include "../localSocket/localsocketipcclient.hpp"


/**
 * \namespace plugin
 */
namespace plugin {
    /*!
     * @brief Interface d'un plugin
     */
    class PluginInterface : public QThread{
        Q_OBJECT

        public:
            virtual QString getPluginName() = 0;

        public slots:
            virtual void run() = 0;
    };

    class PluginImpl : public PluginInterface{
        Q_OBJECT

        friend void WsClient::sendMessage(QString);

        public:
            explicit PluginImpl(QObject *parent = 0);
        private:
            LocalSocketIpcClient *_localSocketIpClient;
            QMap<QUuid, WsClient*> _clients;

        protected:
            void sendMessage(QScriptValue message);
        signals:
            void newConnection(WsClient *newClient);

        private slots:
            void handlNewConnection(QString uuid);
    };
}
Q_DECLARE_INTERFACE(plugin::PluginInterface, "Ewapp plugin interface")
#endif // PLUGIN_HPP
