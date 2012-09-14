#include "settingsmanager.hpp"
#include <iostream>
#include <QFile>
#include <QTextStream>

Logger* SettingsManager::LOG = new Logger(QString(LOG_DIR)+QString(LOG_FILE), LOG_LVL);

SettingsManager::SettingsManager(){
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
    QString filePath = this->directory+"ewapp.conf";
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        LOG->error(tr("Cannot open configuration file : ") + filePath);
        return;
    }

    QTextStream in(&configFile);
    bool first = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.trimmed().at(0) != QChar('#')){
            if(first){
                first = true;
                LOG->info(tr("Applications : "));
            }
            LOG->info(" "+line);
            this->apps.push_back(line);
        }
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
