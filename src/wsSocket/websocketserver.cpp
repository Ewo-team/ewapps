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

#include "websocketserver.hpp"

using namespace ewapps;
/**
 * Definition de WebSocket Server
 */
WebSocketServer::WebSocketServer(short port, Logger *LOG) : QThread(){
    this->LOG = LOG;
    this->port = port;
}

void WebSocketServer::run(){
    websocketpp::server::handler::ptr handler(this);
    websocketpp::server endpoint(handler);
    endpoint.listen(this->port);
}

void WebSocketServer::addApp(QString appName, PluginInterface *app){
    if(this->m_apps.keys().contains(appName)){
        throw new AppAlreadyExistsException(appName+tr(" already exists"));
    }
    this->m_apps.insert(appName, app);
}

void WebSocketServer::supApp(QString appName){
    if(!this->m_apps.keys().contains(appName))
        return;
    this->m_apps.remove(appName);
    foreach(websocketpp::server::connection_ptr co, this->m_connections.keys()){
        if(this->m_connections[co].first == appName){
            co->send("{\"app\":\"close\"}");

            delete m_connections[co].second;
        }
    }
}

void WebSocketServer::validate(websocketpp::server::connection_ptr con){
    bool find = false;
    foreach(QString name, this->m_apps.keys()){
        if(con->get_resource() == "/"+name.toStdString()){
            WebSocketConnection *wsConnection = new WebSocketConnection(con);
            this->m_connections.insert(con, QPair<QString, WebSocketConnection*>(name, wsConnection));
            find = true;
            return;
        }
    }
    if(!find)
        throw(websocketpp::http::exception("",websocketpp::http::status_code::NOT_FOUND));
}

void WebSocketServer::on_open(websocketpp::server::connection_ptr co){
    emit newConnection(this->m_connections[co].first, this->m_connections[co].second);
}

void WebSocketServer::on_close(websocketpp::server::connection_ptr con){
    this->m_connections.remove(con);
}

void WebSocketServer::on_message(websocketpp::server::connection_ptr con, message_ptr msg){
    if (msg->get_opcode() != websocketpp::frame::opcode::TEXT) {
        return;
    }
    this->LOG->debug(tr("new ws message : ") + QString::fromStdString(msg->get_payload()));
    if(!this->m_connections.keys().contains(con)){
        LOG->error(tr("Receive message without validation"));
        return;
    }
    this->m_connections[con].second->receiveNewMessage(QString::fromStdString(msg->get_payload()));
}

/**
 * Definition des exceptions
 */

AppAlreadyExistsException::AppAlreadyExistsException(QString msg){
    this->m_msg = msg;
}

QString AppAlreadyExistsException::getMsg(){
    return this->m_msg;
}
