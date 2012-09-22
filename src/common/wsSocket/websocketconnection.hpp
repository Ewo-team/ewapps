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

#ifndef WEBSOCKETCONNECTION_HPP
#define WEBSOCKETCONNECTION_HPP

#include <QObject>
#include <websocketpp/websocketpp.hpp>

namespace ewapps{

    class WebSocketConnection: public QObject{
        Q_OBJECT
        protected:
            websocketpp::server::connection_ptr m_connection;
        public:
            WebSocketConnection(websocketpp::server::connection_ptr connection);

            void close();
            void receiveNewMessage(QString msg);

            void send(QString msg);

        signals:
            void closed();
            void newMessage(QString msg);
    };
}

#endif // WEBSOCKETCONNECTION_HPP
