#include "localsocketipcserver.hpp"
#include <QLocalSocket>

LocalSocketIpcServer::LocalSocketIpcServer(QString servername, ewapps::Logger *LOG) : QObject() {
    m_server = new QLocalServer(this);
    this->LOG = LOG;
    if (!m_server->listen(servername)) {
        this->LOG->error(tr("Not able to start the local socket server"));
    }

    connect(m_server, SIGNAL(newConnection()), this, SLOT(socket_new_connection()));

}

LocalSocketIpcServer::~LocalSocketIpcServer() {
    this->m_server->close();
    delete this->m_server;
}


void LocalSocketIpcServer::socket_new_connection() {

    QLocalSocket *clientConnection = m_server->nextPendingConnection();

    while (clientConnection->bytesAvailable() < (int)sizeof(quint32))
        clientConnection->waitForReadyRead();


    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);
    if (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
        return;
    }
    QString message;
    in >> message;

    ClientResponse *response = new ClientResponse(message, clientConnection);

    emit messageReceived(response);
}
