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
