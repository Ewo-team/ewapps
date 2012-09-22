#ifndef LOCALSOCKETIPCSERVER_HPP
#define LOCALSOCKETIPCSERVER_HPP

#include <QtNetwork/QLocalServer>
#include "../common/localSocket/clientresponse.hpp"
#include "../common/utils/logger.hpp"

class LocalSocketIpcServer : public QObject{
    Q_OBJECT
    protected:
        ewapps::Logger *LOG;
    public:
        LocalSocketIpcServer(QString servername, ewapps::Logger *LOG);
        ~LocalSocketIpcServer();

    signals:
        void messageReceived(ClientResponse*);

    public slots:
        void socket_new_connection();

    private:
        QLocalServer*       m_server;
};

#endif // LOCALSOCKETIPCSERVER_HPP
