ewapps
======

Plateforme pour faire tourner les applications lourdes d'ewo. Elle lance un daemon qui lui même va gérer les cibles de vie des autes applications (IA, gestion d'evenments aléatoires, ...)

Utilisation
-----

#### Commandes

Il n'y a que trois options :
```bash
$ ewapp start
```
```bash
$ ewapp stop
```
```bash
$ ewapp restart
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