#ifndef CLIENTRESPONSE_HPP
#define CLIENTRESPONSE_HPP

#include <QLocalSocket>

class ClientResponse{
    protected:
        QString message;
        QLocalSocket *socket;

    public:
        ClientResponse(QString message, QLocalSocket * socket);

        QString getMessage();
        void sendResponse(QString repsonse);
};

#endif // CLIENTRESPONSE_HPP
