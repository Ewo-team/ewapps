#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QCoreApplication>
#include <QStringList>
#include "settingsmanager.hpp"

/*!
 * @brief controle du daemon
 * Permet d'envoyer des commandes au daemon
 */
class Controller : public QCoreApplication{
        Q_OBJECT

    protected:
        QStringList args;
        SettingsManager *settings;

    public:
        explicit Controller(int &argc, char **argv, SettingsManager *settings);

        
    signals:
        
    public slots:
        int run();
        void displayResponse(QString);
        
};

#endif // CONTROLLER_HPP
