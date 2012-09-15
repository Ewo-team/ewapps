#include "clientresponse.hpp"

ClientResponse::ClientResponse(QString message, QLocalSocket * socket){
    this->message = message;
    this->socket = socket;
}

QString ClientResponse::getMessage(){
    return this->message;
}

void ClientResponse::sendResponse(QString response){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out << response;
    out.device()->seek(0);

    this->socket->write(block);
    this->socket->flush();
}
