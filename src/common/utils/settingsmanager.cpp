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

using namespace ewapps;

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
    m_apps.clear();
    this->getConfigFileLocation();
    if(this->directory.isEmpty()){
        LOG->error(tr("No config file : ")+this->directory);
        return;
    }

    this->reLoadConfig();
}

void  SettingsManager::reLoadConfig(){
    QString filePath = this->directory+"ewapp.ini";
    this->settings = new QSettings(filePath, QSettings::IniFormat);

    QStringList apps = this->settings->value("apps/list").toStringList();
    foreach(QString app, apps){
        m_apps.insert(this->getAppName(app), app);
    }
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
        QFile file(dir+"/ewapp.ini");
        if(file.exists()){
                this->directory = dir+"/";
            return;
        }

        QFile fileSubDir(dir+"/ewapp/ewapp.ini");
        if(fileSubDir.exists()){
            this->directory = dir+"/ewapp/";
            return;
        }
    }
}

QMap<QString, QString> SettingsManager::getApps(){
    return this->m_apps;
}

QString SettingsManager::getAppName(QString appPath){
    //Get file name : "/etc/name.so" => name.so
    QStringList tbl = appPath.split("/", QString::SkipEmptyParts);
    QString app = tbl[tbl.size() - 1];
    //Get the name "name.so" => name
    return app.split('.', QString::SkipEmptyParts).at(0);
}

QString SettingsManager::getLockFile(){
    QString result = this->settings->value("lockFile").toString();
    return result;
}


QString SettingsManager::getDaemonName(){
    return this->settings->value("daemonName").toString();
}


short SettingsManager::getWsPort(){
    if(!this->settings->contains("wsPort")){
        return 8088;
    }
    return this->settings->value("wsPort").toInt();
}
