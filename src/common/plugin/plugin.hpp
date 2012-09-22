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
#include <QList>
#include "../wsSocket/websocketconnection.hpp"


namespace ewapps {
    /*!
     * @brief Interface d'un plugin
     */
    class PluginInterface : public QThread{
        Q_OBJECT
        public slots:
            virtual void run() = 0;

            virtual void handleNewConnection(WebSocketConnection *connection) = 0;
            virtual void handleNewConnection_intern(WebSocketConnection *connection) = 0;
            virtual void handleCloseConnection_intern() = 0;
        signals:
            void newConnection(WebSocketConnection *connection);
    };
}
Q_DECLARE_INTERFACE(ewapps::PluginInterface, "Ewapp plugin interface")
namespace ewapps {
    class PluginImpl : public PluginInterface{
        Q_OBJECT
        Q_INTERFACES(ewapps::PluginInterface)

        public:
            explicit PluginImpl();
        protected:
            QList<WebSocketConnection*> m_connections;
        protected:
            void broadCast(QString msg);
        public slots:
            virtual void handleNewConnection_intern(WebSocketConnection *connection);
            virtual void handleCloseConnection_intern();
    };
}
#endif // PLUGIN_HPP
