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

#include "settingsmanager.hpp"
#include <QFile>
#include <QTextStream>
#include <iostream>


SettingsManager::SettingsManager(Logger *LOG){
    this->LOG = LOG;
    this->loadConfig();
}


SettingsManager::~SettingsManager(){

}

QString SettingsManager::getDirectory(){
    return this->directory;
}

void  SettingsManager::loadConfig(){
    this->getConfigFileLocation();
    if(this->directory.isEmpty()){
        LOG->error(tr("No config file"));
        return;
    }
    QString filePath = this->directory+"ewapp.ini";

    this->settings = new QSettings(filePath, QSettings::IniFormat);

    this->apps = this->settings->value("apps/list").toStringList();
}


void  SettingsManager::getConfigFileLocation(){
    char *cStrPath = getenv("PATH");
    if(cStrPath == NULL)
        return;

    QString path(cStrPath);

    QStringList dirs = path.split(":");
    dirs.push_front("/var/local/");
    dirs.push_front("/var/");
    dirs.push_front("/usr/local/etc");
    dirs.push_front("/etc");
    QString dir;
    foreach(dir, dirs){
        QFile file(dir+"/ewapp.conf");
        if(file.exists()){
                this->directory = dir+"/";
            return;
        }

        QFile fileSubDir(dir+"/ewapp/ewapp.conf");
        if(fileSubDir.exists()){
            this->directory = dir+"/ewapp/";
            return;
        }
    }
}

QStringList SettingsManager::getApps(){
    return this->apps;
}

QStringList SettingsManager::getAppsNames(){
    QStringList result;
    foreach(QString appPath, this->apps){
        //Get file name : "/etc/name.so" => name.so
        QStringList tbl = appPath.split("/", QString::SkipEmptyParts);
        QString app = tbl[tbl.size() - 1];
        //Get the name "name.so" => name
        result.push_back(app.split('.', QString::SkipEmptyParts).at(0));
    }
    return result;
}

QString SettingsManager::getLockFile(){
    return this->settings->value("lockFile").toString();
}


QString SettingsManager::getDaemonName(){
    return this->settings->value("daemonName").toString();
}
