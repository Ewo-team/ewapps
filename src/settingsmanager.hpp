#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>
#include <QStringList>

class SettingsManager : public QObject{
        Q_OBJECT

    protected:
        QStringList apps;
    public:
        SettingsManager();
        ~SettingsManager();


    protected:
        void loadConfig();
        QString getConfigFileLocation();
};

#endif // SETTINGSMANAGER_HPP
