ewapps
======

version : 0.0.2

Plateforme pour faire tourner les applications lourdes d'ewo. Elle lance un daemon qui lui même va gérer les cibles de vie des autes applications (IA, gestion d'evenments aléatoires, ...)

Utilisation
-----

#### Commandes

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

La configuration elle se fait via fichier. Ce fichier s'appel ewapp.conf et doit se trouver dans la PATH du système, et peut se trouver dans un sous dossier ewapp (ou pas).
Sa structure est très simple
```bash
#Un commentaire
#chemin relatif au fichier de config
ewia.so
#chemin absolu
/usr/local/etc/ewapp/ewevent.so
```

Creation d'un plugin
-----

Un plugin se présente sous la forme d'une librairie partagée (.so sous unix). Je dois encore voir les mécanismes de Qt à ce niveau là, mais il devront surement dériver d'une certaine classe, ou au moins posséder certaines méthodes.

Un plugin va pouvoir accéder à certains services fournis :
* websocket : l'application aura le droit à un service websocket (un par appli pour éviter les collisons de nom, donc chaque appli fera sa popote interne pour différencier les fonctions). Un service de génération de tokken sera aussi fourni.
* système de log
* communication avec l'api ewo
* communication interne avec d'autres applis
* système d'envoie de mail
* gestion de fichier de config
* ...

Tout ceci sera explicité dans la doc plus tard