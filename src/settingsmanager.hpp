#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>
#include <QStringList>
#include "logger.hpp"
/*!
 * @brief Gestion des options
 * Ouvre les fichiers de conf et récupère les valeurs, peut aussi les modifier
 */
class SettingsManager : public QObject{
        Q_OBJECT

    protected:
        Logger *LOG;

        QString directory;
        QStringList apps;
    public:
        SettingsManager(Logger *LOG);
        ~SettingsManager();

    public:
        QString getDirectory();
        QStringList getApps();

    protected:
        void loadConfig();
        void getConfigFileLocation();
};

#endif // SETTINGSMANAGER_HPP
