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

#include "websocketconnection.hpp"

using namespace ewapps;

WebSocketConnection::WebSocketConnection(websocketpp::server::connection_ptr connection){
    this->m_connection = connection;
}

void WebSocketConnection::close(){
    emit closed();
}

void WebSocketConnection::receiveNewMessage(QString msg){
    emit newMessage(msg);
}

void WebSocketConnection::send(QString msg){
    this->m_connection->send(msg.toStdString());
}
