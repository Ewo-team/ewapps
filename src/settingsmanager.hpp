//////////////////////////////////////////////////////////////////////////
//
//             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// Version 2, December 2004
//
// Copyright (C) 2012 Benjamin Herbomez (benjamin.herbomez@gmail.com)
//
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
// 0. You just DO WHAT THE FUCK YOU WANT TO.
//
//////////////////////////////////////////////////////////////////////////

#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QSettings>
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
        QSettings *settings;

        QString directory;
        QStringList apps;
    public:
        SettingsManager(Logger *LOG);
        ~SettingsManager();

    public:
        QString getDirectory();
        QStringList getApps();
        QStringList getAppsNames();
        QString getLockFile();
        QString getDaemonName();

    protected:
        void loadConfig();
        void getConfigFileLocation();
};

#endif // SETTINGSMANAGER_HPP
