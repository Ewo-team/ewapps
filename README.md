ewapps
======

version : 0.0.6

Plateforme pour faire tourner les applications lourdes d'ewo. Elle lance un daemon qui lui même va gérer les cibles de vie des autes applications (IA, gestion d'evenments aléatoires, ...)

Installation
-----

### Prérequis

Récupèrer le code source via git
```bash
$ git clone 
```
L'application utilise la lib [websocket++](https://github.com/zaphoyd/websocketpp) qui est définie entant que sous module, il faut donc exécuter la commande suivante :
```bash
$ git submodule init
$ git submodule update
```
Ensuite, étant donné qu'ewapps est basé sur Qt4 il faut avoir les libs d'installée, à voir en fonction de l'OS.
Enfin, il faut récupérer [segvcatch](http://code.google.com/p/segvcatch/), une lib qui permet la gestion des erreurs dans les plugins, à téléchartger [ici](http://code.google.com/p/segvcatch/downloads/detail?name=segvcatch-0.9.1.zip&can=2&q=)

### Installation

#### Websocket++

Voir le guide de la lib [ici](https://github.com/zaphoyd/websocketpp/wiki/Build-Library) 

#### Segvcatch

C'est du cmake, donc dans le dossier du makefile
```bash
$ cmake .
$ make
$ sudo make install
``` 

#### Ewapps

Très simple aussi, il suffit de définir le type de build dans le fichier ewapp.pro (debug ou release dans la variable CONFIG) et après

```bash
$ qmake ewapp.pro
$ make
``` 

Et voila, y a plus qu'à

Utilisation
-----

### Commandes

Il n'y a que quatre options :
- démarrer des applications (toutes si aucun argument)

```bash
$ ewapp start [appname1] [appname2] [...]
```

- arrêter des applications (toutes si aucun argument)

```bash
$ ewapp stop [appname1] [appname2] [...]
```

- redémarrer des applications (toutes si aucun argument)

```bash 
$ ewapp restart [appname1] [appname2] [...]
```

- connaitre l'état d'applications (toutes si aucun argument)

```bash 
$ ewapp state [appname1] [appname2] [...]
```

### Configuration

La configuration elle se fait via fichier INI. Ce fichier s'appel ewapp.ini et doit se trouver dans /etc/ ou usr/local/etc/ oudans la PATH du système, et peut se trouver dans un sous dossier ewapp (ou pas).
Sa structure est très simple
```ini
[General]
; Fichier de lock
lockFile=/var/lock/ewapp.lock
; Nom à donner au daemon pour la communication interne
daemonName=ewapps

[apps]
; liste des applications à lancer
list=	/usr/local/ewapp/admin.so,
	v3.so
```

Creation d'un plugin
-----

Un plugin se présente sous la forme d'une librairie partagée (.so sous unix).
Concraitement voici comment faire via un petit exemple. Si on veut faire un chat voici comment faire :

créer un fichier de projet QT chat.pro

```bash
TEMPLATE = lib

QT       += core network script
QT       -= gui

TARGET   = chat
CONFIG   += release plugin
CONFIG   -= app_bundle
```

Dans ce projet, il faut ensuite créer une classe principale, Chat, avec le header suivant :

```Cpp

#ifndef CHAT_HPP
#define CHAT_HPP

#include "common/plugin/plugin.hpp"
#include "common/wsSocket/websocketconnection.hpp"

class Chat : public ewapps::PluginImpl{
    Q_OBJECT
    Q_INTERFACES(ewapps::PluginInterface)

    public:
        explicit Chat();
        virtual QString getPluginName();
    signals:
        
    public slots:
        virtual void run();
        virtual void handleNewConnection(ewapps::WebSocketConnection *connection);
        void handleNewMessage(QString msg);
};
#endif // CHAT_HPP
```

toutes les dépendances pour faire un plugin sont dans le sous dossier common/

Une dernière chose, dans le fichier d'implémentation de la classe chat il faut ajouter, en dernière ligne:

```cpp
Q_EXPORT_PLUGIN2(chat, Chat);
```

chat est le nom du plugin (variable TARGET), et Chat celui de la classe qui implémente le plugin