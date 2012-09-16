#ifndef LOCALSOCKETIPCSERVER_HPP
#define LOCALSOCKETIPCSERVER_HPP

#include <QtNetwork/QLocalServer>
#include "clientresponse.hpp"

class LocalSocketIpcServer : public QObject
{
        Q_OBJECT
    public:
        LocalSocketIpcServer(QString servername, QObject *parent);
        ~LocalSocketIpcServer();

    signals:
        void messageReceived(ClientResponse*);

    public slots:
        void socket_new_connection();

    private:
        QLocalServer*       m_server;
};

#endif // LOCALSOCKETIPCSERVER_HPP
