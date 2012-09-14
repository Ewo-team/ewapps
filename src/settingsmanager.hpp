#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>
#include <QStringList>
#include "logger.hpp"

class SettingsManager : public QObject{
        Q_OBJECT

    protected:
        static Logger *LOG;

        QString directory;
        QStringList apps;
    public:
        SettingsManager();
        ~SettingsManager();

    public:
        QString getDirectory();

    protected:
        void loadConfig();
        void getConfigFileLocation();
};

#endif // SETTINGSMANAGER_HPP
