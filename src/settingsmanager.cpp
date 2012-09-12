#include "settingsmanager.hpp"
#include <iostream>
#include <QFile>
#include <QTextStream>

SettingsManager::SettingsManager(){
    this->loadConfig();
}


SettingsManager::~SettingsManager(){

}

void  SettingsManager::loadConfig(){
    QString filePath = this->getConfigFileLocation();
    if(filePath.isEmpty()){
        std::cerr << "No config file" << std::endl;
        return;
    }
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cerr << "Cannot open configuration file : " << filePath.toStdString() << std::endl;
        return;
    }

     QTextStream in(&configFile);
     while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.trimmed().at(0) != QChar('#')){
            std::cout << line.toStdString() << std::endl;
        }
     }
}


QString  SettingsManager::getConfigFileLocation(){
    char *cStrPath = getenv("PATH");
    if(cStrPath == NULL)
        return QString();

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
             return dir+"/ewapp.conf";
        }

        QFile fileSubDir(dir+"/ewapp/ewapp.conf");
        if(fileSubDir.exists()){
             return dir+"/ewapp/ewapp.conf";
        }
    }
    return "";
}
