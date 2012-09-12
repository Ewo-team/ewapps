#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject{
        Q_OBJECT

    protected:
        QSettings *settings;
    public:
        SettingsManager();
        ~SettingsManager();

        void setRunning(bool isRunning);
        bool isRunning();
};

#endif // SETTINGSMANAGER_HPP
