#include "settingsmanager.hpp"

SettingsManager::SettingsManager(){
    this->settings = new QSettings("ewo", "ewapps");
}


SettingsManager::~SettingsManager(){
    delete this->settings;
}


void SettingsManager::setRunning(bool isRunning){
    this->settings->setValue("isRunning", isRunning);
}

bool SettingsManager::isRunning(){
    return this->settings->value("isRunning", "false") == "true";
}
