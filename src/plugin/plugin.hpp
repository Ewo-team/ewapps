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

#include <QObject>
#include <QtPlugin>
#include <QMap>
#include <QUuid>
#include <QtScript>
#include "wsclient.hpp"
#include "../localSocket/localsocketipcclient.hpp"


/**
 * \namespace plugin
 */
namespace plugin{
    /*!
     * @brief Interface d'un plugin
     */
    class Plugin : public QObject{
        Q_OBJECT

        friend void WsClient::sendMessage(QString);

        private:
            LocalSocketIpcClient *_localSocketIpClient;
            QMap<QUuid, WsClient*> _clients;

        public:
            explicit Plugin(QObject *parent = 0);
            virtual QString getPluginName() = 0;

        protected:
            void sendMessage(QScriptValue message);
        signals:
            void newConnection(WsClient *newClient);

        private slots:
            void handlNewConnection(QString uuid);

        public slots:
            virtual void run() = 0;
    };
}
Q_DECLARE_INTERFACE(plugin::Plugin, "Ewapp plugin interface")
#endif // PLUGIN_HPP
