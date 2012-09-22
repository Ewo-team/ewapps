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

#ifndef WEBSOCKETSERVER_HPP
#define WEBSOCKETSERVER_HPP

#include <QThread>
#include <QMap>
#include <QList>
#include <QPair>
#include <websocketpp/websocketpp.hpp>
#include "../common/wsSocket/websocketconnection.hpp"
#include "../common/plugin/plugin.hpp"
#include "../common/utils/logger.hpp"


namespace ewapps{
    class WebSocketServer : public QThread, public websocketpp::server::handler{
        Q_OBJECT
        protected:
            QMap<websocketpp::server::connection_ptr,QPair<QString, WebSocketConnection*> >  m_connections;
            QMap<QString, PluginInterface*> m_apps;
            Logger *LOG;
            short port;
        public:
            explicit WebSocketServer(short port, Logger *LOG);

            virtual void run();

            void addApp(QString appName, PluginInterface *app);
            void supApp(QString appName);
        protected:
            void validate(websocketpp::server::connection_ptr con);
            void on_open(websocketpp::server::connection_ptr con);
            void on_close(websocketpp::server::connection_ptr con);
            void on_message(websocketpp::server::connection_ptr con, message_ptr msg);
        signals:
            void newConnection(QString appName, WebSocketConnection *co);
        public slots:
    };

    class AppAlreadyExistsException{
        private:
            QString m_msg;
        public:
            explicit AppAlreadyExistsException(QString msg);
            QString getMsg();
    };
}
#endif // WEBSOCKETSERVER_HPP
