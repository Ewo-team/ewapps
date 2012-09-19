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

namespace plugin{
    PluginImpl::PluginImpl(QObject *parent) {

    }

    void PluginImpl::handlNewConnection(QString uuid){
        WsClient *client = new WsClient(uuid, this);
        this->_clients.insert(uuid, client);
        emit newConnection(client);
    }

    void PluginImpl::sendMessage(QScriptValue message){
        message.toString();
    }
}
