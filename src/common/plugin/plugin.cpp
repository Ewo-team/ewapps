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

#include "plugin.hpp"

using namespace ewapps;


PluginImpl::PluginImpl(): PluginInterface(){
    connect(this, SIGNAL(newConnection(WebSocketConnection*)), this, SLOT(handleNewConnection(WebSocketConnection*)));
}

void PluginImpl::broadCast(QString msg){
    foreach(WebSocketConnection *co, this->m_connections){
        co->send(msg);
    }
}

void PluginImpl::handleNewConnection_intern(WebSocketConnection *connection){
    this->m_connections.push_back(connection);

    connect(connection, SIGNAL(closed()), this, SLOT(handleCloseConnection_intern()));
    emit newConnection(connection);
}

void PluginImpl::handleCloseConnection_intern(){
    int index = this->m_connections.indexOf(qobject_cast<WebSocketConnection*>(this->sender()));
    if(index > 0)
        this->m_connections.removeAt(index);
}

