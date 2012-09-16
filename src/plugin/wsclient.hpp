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

#ifndef WSCLIENT_HPP
#define WSCLIENT_HPP

#include <QObject>
#include <QUuid>
#include <QtScript/QScriptEngine>

/**
 * \namespace plugin
 */
namespace plugin{

    class Plugin;

    /*!
     * @brief Client WebSocket
     */
    class WsClient: public QObject{
        Q_OBJECT

        private:
            QUuid uuid;
            Plugin *plugin;
        public:
            WsClient(QUuid uuid, Plugin *plugin);

        private:
            void sendMessage(QString message);
            void sendMessage(QScriptValue message);
        signals:
            QString newMessage();
            void close();
    };
}
#endif // WSCLIENT_HPP
