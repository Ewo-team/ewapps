#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QCoreApplication>
#include <QStringList>

class Controller : public QCoreApplication{
        Q_OBJECT

    protected:
            QStringList args;

    public:
        explicit Controller(int &argc, char **argv);

        
    signals:
        
    public slots:
        int run();
        void displayResponse(QString);
        
};

#endif // CONTROLLER_HPP
